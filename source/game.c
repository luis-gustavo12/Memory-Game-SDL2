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


int InitGame(Game* game) {

    game->gameButtonsSize = 0;
    game->gameLogicState = GameLogicState_None;

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

    // Set stack to zero
    game->stackSize = 0;
    memset(&game->memoryQueue, 0, sizeof(MemoryQueue));
    game->memoryQueue.first = NULL;
    game->memoryQueue.last = NULL;
    game->memoryQueue.size = 0;

    // start game over buttons
    SetButton(&game->gameOver.exitButton, "Exit");
    SetButtonBackGroundPositions(&game->gameOver.exitButton, 320, 180, 350, 150);
    SetButtonTextPositionsByValue(&game->gameOver.exitButton, 320, 180, 350, 150);
    SetColorByValue(&game->gameOver.exitButton.colorButtonBackground, 222, 129, 180, 255);
    SetButtonBackgroundColorByValue(&game->gameOver.exitButton, 136, 71, 199, 250);

    

    return 1;
}

void RenderGameScreen(SDL_Renderer* renderer, Game* game, TTF_Font* font) {

    MouseCoordinate mouse = game->mouseCoordinate;

    switch (game->gameLogicState) {

    case GameLogicState_GameOver:
        RenderGameOverScreen(renderer, mouse, game, font);
        break;


    default: {

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
            strcpy(gameLogicStateText, "Hit the squares!!");
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

    switch (game->gameLogicState)
    {
    case GameLogicState_GameOver: {
        ProcessGameOver(game);
        break;
    }

    default: {
        // Setting state for the first time
        if (game->gameLogicState == GameLogicState_None) game->gameLogicState = GameLogicState_Filling;

        printf("---------------------------------------------------------------\n");
        printf("LOGIC STATE: %d\n", game->gameLogicState);
        printf("STACK SIZE: %d\n", game->memoryQueue.size);

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
                Enqueue(&game->memoryQueue, &game->map[i]);
                game->gameLogicState = GameLogicState_Guessing;
                return;
            }

            else if (game->gameLogicState == GameLogicState_Guessing || game->gameLogicState == GameLogicState_Awaiting) {

                // checking if it was the right square
                if (CheckMapInQueue(game->memoryQueue, game->map[i], game->memoryQueue.size)) {
                    if (game->gameLogicState == GameLogicState_Guessing) {
                        game->score++;
                    }

                    if (game->memoryQueue.size == game->score)
                        game->gameLogicState = GameLogicState_Filling; // goes back to filling the stack

                }
                else {
                    printf("YOU LOST\n");
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

            printf("INSIDE\n");
            return 1;
        }


    printf("OUTSIDE\n");
    return 0;
}


/* QUEUE RELATED OPERATIONS */

void Enqueue(MemoryQueue* queue, GameButtonsMap* map) {

    GameButtonsMap* newMap = map;

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



/* QUEUE RELATED OPERATIONS -> END*/


void ResetGame(Game* game) {
    memset(&game->memoryQueue, 0, sizeof(game->memoryQueue));
    game->score = 0;
    game->attemptHits = 0;
}

int CheckMapInQueue(MemoryQueue queue, GameButtonsMap map, int stackSize) {

    GameButtonsMap* iterator = queue.first;
    int i = 0;
    printf("STACK SIZE-%s : %d\n", __func__ ,stackSize);

    while (i < stackSize) {

        printf("ITERATOR: %d\n", i);
        printf("R: %d G: %d B: %d A: %d\n", iterator->color.r, iterator->color.g, iterator->color.b, iterator->color.a);
        printf("MAP\n");
        printf("R: %d G: %d B: %d A: %d\n", map.color.r, map.color.g, map.color.b, map.color.a);
        

        if (ColorsAreEqual(iterator->color, map.color) == true) {
            printf("SQUARE HIT WAS INSIDE THE QUEUE\n");
            return 1;
        }

        i++;

    }

    printf("SQUARE WAS NOT PART OF THE QUEUE\n");

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

    //SDL_SetRenderDrawColor(renderer, 128, 0, 128, 255);

    //SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    //SDL_RenderFillRect(renderer, &game->gameOver.exitButton.buttonBackGround);
    


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

    int hit = false;

    if (HasHitButton(game->mouseCoordinate, game->gameOver.exitButton)) {

        printf("here\n");
        game->gameState = States_EXIT;
        hit = true;
        return;

    }

}

int HasHitButton(MouseCoordinate mouse, Button button) {

    return ( (mouse.xClick >= button.buttonBackGround.x) && (mouse.xClick <= (button.buttonBackGround.x + button.buttonBackGround.w) ) ) &&
           ( (mouse.yClick >= button.buttonBackGround.y) && (mouse.yClick <= (button.buttonBackGround.y + button.buttonBackGround.h) ) );


}
