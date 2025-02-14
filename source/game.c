#include "game.h" 



SDL_Color gameColors[4] = {
    {204, 0, 0, 255},     // RED
    {41, 134 ,204, 255},  // BLUE
    {255, 217, 102, 255}, // YELLOW
    {106, 168, 79, 255}   // GREEN
};


// Each button will be represented by one of gameColors
SDL_Rect gameButtonsBackground[4] = {

    {225, 25, 300, 300},    // RED
    {225, 375, 300, 300},   // BLUE
    {650, 25, 300, 300},   // YELLOW
    {650, 375, 300, 300}   // GREEN

};

char colorsArray [4] [20] = {
    {"Red"}, {"Blue"}, {"Yellow"}, {"Green"}
};


Game* InitGame(void) {

    Game* game = (Game*)malloc(sizeof(Game));

    if (game == NULL) return NULL;

    game->gameButtonsSize = 0;
    game->gameLogicState = GameLogicState_None;
    game->guessingCount = 0;

    // The idea in the game is basically have buttons for colors. By now, we will choose 4,
    // but in the future, the idea is to have some kind of dificulty in it.


    // fill Game struct
    for (int i = 0; i < 4; i++) {

        Button btn;

        SetButton(&btn, NULL);

        SetButtonByColorSDL(&btn, gameButtonsBackground[i]);

        game->gameButtons[i] = btn;
        game->map[i].color = gameColors[i];
        game->map[i].rectangle = gameButtonsBackground[i];
        game->gameButtonsSize++;
        strcpy(game->map[i].squareColorName, colorsArray[i]);
        SetButtonName(&btn, colorsArray[i]);

    }

    // score button
    SetButton(&game->scoreButton, "Score: ");
    SetButtonBackGroundPositions(&game->scoreButton, 1000, 500, 250, 125);
    SetButtonTextPositions(&game->scoreButton);
    SetColorByValue(&game->scoreButtonColor, 120, 120, 120, 255);
    // game->scoreButtonColor.r = 120;
    // game->scoreButtonColor.g = 120;
    // game->scoreButtonColor.b = 120;
    // game->scoreButtonColor.a = 255;

    // set game logic state button
    SetButton(&game->gameLogicStateButton, "State");
    SetButtonBackGroundPositions(&game->gameLogicStateButton, 1000, 250, 250, 125);
    SetButtonTextPositionsByValue(&game->gameLogicStateButton, 1010, 240, 220, 100);
    SetColorByValue(&game->gameLogicStateButtonColor, 222, 129, 180, 255);

    game->score = 0;
    game->attemptHits = 0;

    // Set stacks to zero
    game->stackSize = 0;
    //memset(&game->memoryQueue, 0, sizeof(MemoryQueue));
    //game->memoryQueue.first = NULL;
    //game->memoryQueue.last = NULL;
    //game->memoryQueue.size = 0;

    game->memoryQueue = InitQueue();

    if (!game->memoryQueue) {
        Log("Error in memory queue!!", LogLevel_ERROR);
        return 0;
    }
    game->guessingQueue = InitQueue();

    if (!game->guessingQueue) {
        Log("Error in guessing queue!!", LogLevel_ERROR);
        return 0;
    }


    // start game over buttons
    SetButton(&game->gameOver.exitButton, "Exit");
    SetButtonBackGroundPositions(&game->gameOver.exitButton, 320, 50, 350, 150);
    SetButtonTextPositionsByValue(&game->gameOver.exitButton, 320, 50, 350, 150);
    SetColorByValue(&game->gameOver.exitButton.colorButtonBackground, 222, 129, 180, 255);
    SetButtonBackgroundColorByValue(&game->gameOver.exitButton, 136, 71, 199, 250);

    SetButton(&game->gameOver.playAgainButton, "Play Again");
    SetButtonBackGroundPositions(&game->gameOver.playAgainButton, 320, 350, 350, 150);
    SetButtonTextPositionsByValue(&game->gameOver.playAgainButton, 320, 350, 350, 150);
    SetColorByValue(&game->gameOver.playAgainButton.colorButtonBackground, 222, 129, 180, 255);
    SetButtonBackgroundColorByValue(&game->gameOver.playAgainButton, 136, 71, 199, 250);
    

    return game;
}

void RenderGameScreen(SDL_Renderer* renderer, Game* game, TTF_Font* font) {

    MouseCoordinate mouse = game->mouseCoordinate;

    switch (game->gameLogicState) {

    case GameLogicState_GameOver:
        RenderGameOverScreen(renderer, mouse, game, font);
        break;



    default: {

        if (game->gameLogicState == GameLogicState_None || game->gameLogicState == GameLogicState_Guessing) 
            SDL_SetRenderDrawColor(renderer, 129, 150, 143, 255); // set background to a greenish gray
        else 
            SDL_SetRenderDrawColor(renderer, 188, 188, 188, 255); // set background to gray


        SDL_RenderClear(renderer);

        for (int i = 0; i < game->gameButtonsSize; i++) {

            SDL_Rect copy = game->gameButtons[i].buttonBackGround;

            SDL_SetRenderDrawColor(renderer, game->map[i].color.r, game->map[i].color.g,
                game->map[i].color.b, game->map[i].color.a);
            SDL_RenderFillRect(renderer, &copy);

        }


        char scoreText[40];
        char gameLogicStateText[40];

        sprintf(scoreText, "Score: %d", game->score);

        // show score at some side
        SetButton(&game->scoreButton, scoreText);
        RenderButton(renderer, font, &game->scoreButton, game->scoreButtonColor);

        // show game logic state
        if (game->gameLogicState == GameLogicState_Filling) {
            strcpy(gameLogicStateText, "Fill the sequence!!");
        }
        else if (game->gameLogicState == GameLogicState_Guessing || game->gameLogicState == GameLogicState_None) {
            strcpy(gameLogicStateText, "Try to guess it!!");
        }

        SetButton(&game->gameLogicStateButton, gameLogicStateText);
        RenderButton(renderer, font, &game->gameLogicStateButton, game->scoreButtonColor);


        SDL_RenderPresent(renderer);


        break;
    }

      
    }
    



}

void ProcessGameLogic(Game* game) {

    int hit = 0; // 1 if hit the square, 0, if don't
    int i;
    MouseCoordinate mouse = game->mouseCoordinate;

    switch (game->gameLogicState) {
    case GameLogicState_GameOver: {
        ProcessGameOver(game);
        break;
    }

    default: {
        // Setting state for the first time
        if (game->gameLogicState == GameLogicState_None) game->gameLogicState = GameLogicState_Filling;
        {
            char dbg[32];
            Log("---------------------------------------------------------------", LogLevel_INFO);

            sprintf(dbg, "LOGIC STATE: %d", game->gameLogicState);
            Log(dbg, LogLevel_INFO);
            sprintf(dbg, "STACK SIZE: %d", game->memoryQueue->size);
            Log(dbg, LogLevel_INFO);
            DebugStack(game);
        }

        // Check through map if square was hit
        for (i = 0; i < game->gameButtonsSize; i++) {

            GameButtonsMap currentMap = game->map[i];

            if (HasHitSquare(mouse, currentMap) == true) {
                hit = true;
                break;
            }

        }

        if (hit == true) {

            if (game->gameLogicState == GameLogicState_Filling) {
                Enqueue(game->memoryQueue, &game->map[i]);
                game->gameLogicState = GameLogicState_Guessing;
                game->guessingCount = 0;
                return;
            }



            else if (game->gameLogicState == GameLogicState_Guessing || game->gameLogicState == GameLogicState_Awaiting) {

                Enqueue(game->guessingQueue, &game->map[i]);

                game->guessingCount++;

                // checking if it was the right square
                if (CheckSquareOrderOnQueue(game)) {    

                    

                    if (game->guessingCount == game->memoryQueue->size) {
                        game->gameLogicState = GameLogicState_Filling; // goes back to filling the stack
                        game->score += game->memoryQueue->size;
                        game->guessingCount = 0;
                        ResetQueue(game->guessingQueue);
                    }

                }
                else {
                    Log("YOU LOST", LogLevel_INFO);
                    game->gameLogicState = GameLogicState_GameOver;
                }

            }


        }

        break;
    }

    }
    
    
}

int HasHitSquare(const MouseCoordinate mouse, GameButtonsMap map) {

    if ( (mouse.xClick >= map.rectangle.x && mouse.xClick <= (map.rectangle.x + map.rectangle.w) )  && 
        (mouse.yClick >= map.rectangle.y && mouse.yClick <= (map.rectangle.y + map.rectangle.h))  ) {

            Log("INSIDE", LogLevel_INFO);
            return 1;
        }


    Log("OUTSIDE", LogLevel_INFO);
    return 0;
}


/* QUEUE RELATED OPERATIONS */

void Enqueue(MemoryQueue* queue, GameButtonsMap* map) {

    GameButtonsMap* newMap = (GameButtonsMap*)malloc(sizeof(GameButtonsMap) );

    *newMap = *map;
    newMap->next = NULL;

    if (!newMap) return;

    if (queue->first == NULL) {
        queue->first = newMap;
        queue->last = newMap;
    }

    else {
        queue->last->next = newMap;
        queue->last = newMap;

    }

    queue->size++;

}

GameButtonsMap* GetMap(MemoryQueue* queue, int index) {

    if (queue->first == NULL) return NULL;
    int count = 0;

    for (GameButtonsMap* iterator = queue->first; iterator != NULL; iterator = iterator->next) {
        if (index == count) {
            return iterator;
        }
        count++;
    }

    return NULL;
}

MemoryQueue* InitQueue(void) {

    MemoryQueue* newQueue = (MemoryQueue*)malloc (sizeof(MemoryQueue) );

    if (!newQueue) {
        return NULL;
    }

    newQueue->first = NULL;
    newQueue->last = NULL;
    newQueue->size = 0;
    return newQueue;
}

void ResetQueue(MemoryQueue* queue) {

    if (queue->size == 0) return;
    GameButtonsMap* iterator = queue->first;

    while ( iterator != NULL) {

        GameButtonsMap* aux = iterator->next;
        free(iterator);
        iterator = aux;

    }

    queue->size = 0;
    queue->first = NULL;
    queue->last = NULL;

}



/* QUEUE RELATED OPERATIONS -> END*/


void ResetGame(Game* game) {
    ResetQueue(game->memoryQueue);
    ResetQueue(game->guessingQueue);
    game->score = 0;
    game->attemptHits = 0;
}

int CheckSquareOrderOnQueue(Game* game) {

    int index; 
    char dbg[64];

    index = game->guessingCount - 1; // it has to be -1, because the guess is added to the queue, so its size increases by 1

    GameButtonsMap* memoryButton = GetMap(game->memoryQueue, index);
    GameButtonsMap* guessingButton = GetMap(game->guessingQueue, index);

    snprintf(dbg, sizeof(dbg), "The user hit the collor [%s] at index %d", guessingButton->squareColorName, index);
    Log(dbg, LogLevel_INFO);

    snprintf(dbg, sizeof(dbg), "The memory queue at index %d is [%s]", index, memoryButton->squareColorName);
    Log(dbg, LogLevel_INFO);

    if (!memoryButton || !guessingButton) {
        Log("ERROR!!", LogLevel_ERROR);
        game->gameState = States_EXIT;
        return 0;
    }

    if (!memoryButton) {
        GameButtonsMap* dbg = GetMap(game->memoryQueue, index);

        Log("NOT MEMORY BUTTON", LogLevel_FATAL);
    }

    if (memoryButton == NULL) {
        Log("NULL HERE!", LogLevel_INFO);
    }

    

    if (memoryButton) {



        if (!strcmp(memoryButton->squareColorName, guessingButton->squareColorName)) {

            Log("THEY'VE HIT THE SAME SQURE!!", LogLevel_INFO);
            return 1;

        }

    }


    return 0;

}

int ColorsAreEqual(SDL_Color color1, SDL_Color color2) {
    return ( (color1.r = color2.r) && (color1.g == color2.g) && (color1.b == color2.b) && (color1.a = color2.a) );
}

void RenderGameOverScreen(SDL_Renderer* renderer, const MouseCoordinate mouse, Game* game, TTF_Font* font) {

    SDL_SetRenderDrawColor(renderer, 0, 153, 224, 88);

    SDL_RenderClear(renderer);

    SDL_Color color = game->gameOver.exitButton.colorButtonBackground;

    RenderButtonEx(renderer, font, &game->gameOver.exitButton);
    
    RenderButtonEx(renderer, font, &game->gameOver.playAgainButton);

    SDL_RenderPresent(renderer);

}

int ClickedInside(Game* game, const Button button) {

    SDL_Rect rect = button.buttonBackGround;
    MouseCoordinate mouse = game->mouseCoordinate;

    rect.h += rect.y;
    rect.w += rect.x;

    return ((mouse.xClick >= rect.x && mouse.yClick >= rect.y) && (mouse.yClick <= rect.h && mouse.xClick <= rect.w));

}

void ProcessGameOver(Game* game) {

    if (HasHitButton(game->mouseCoordinate, game->gameOver.exitButton)) {

        game->gameState = States_EXIT;
        return;

    }
    else if (HasHitButton(game->mouseCoordinate, game->gameOver.playAgainButton)) {

        game->gameState = States_GAME;
        game->gameLogicState = GameLogicState_Filling;
        printf("HERE!");
        ResetGame(game);
        return;

    }

}

int HasHitButton(MouseCoordinate mouse, Button button) {

    return ( (mouse.xClick >= button.buttonBackGround.x) && (mouse.xClick <= (button.buttonBackGround.x + button.buttonBackGround.w) ) ) &&
           ( (mouse.yClick >= button.buttonBackGround.y) && (mouse.yClick <= (button.buttonBackGround.y + button.buttonBackGround.h) ) );


}

void DebugStack(Game* game) {

    Log("DebugStack BEGIN!!!", LogLevel_INFO);

    Log("*** *** *** MEMORY-STACK *** *** ***", LogLevel_INFO);

    GameButtonsMap* iterator = game->memoryQueue->first;

    for (int i = 0; i < game->memoryQueue->size; i++) {

        if (!iterator) {
            Log("memoryQueue Iterator is null!!", LogLevel_WARN);
            continue;
        }

        char dbg[32];

        sprintf(dbg, "Position: %d", i);
        Log(dbg, LogLevel_INFO);
        sprintf(dbg, "Color: [%s]", iterator->squareColorName);
        Log(dbg, LogLevel_INFO);

        iterator = iterator->next;

    }


    Log("*** *** *** GUESSING-STACK *** *** ***", LogLevel_INFO);

    iterator = game->guessingQueue->first;

    for (int i = 0; i < game->guessingQueue->size; i++) {

        if (!iterator) {
            Log("guessingQueue Iterator is null!!", LogLevel_WARN);
            continue;
        }

        char dbg[32];

        sprintf(dbg, "Position: %d", i);
        Log(dbg, LogLevel_INFO);
        sprintf(dbg, "Color: [%s]", iterator->squareColorName);
        Log(dbg, LogLevel_INFO);

        iterator = iterator->next;

    }


}
