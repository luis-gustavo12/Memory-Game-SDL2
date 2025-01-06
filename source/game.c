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




int InitGame(Game* game) {

    game->gameButtonsSize = 0;

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

    }

    // score button
    SetButton(&game->scoreButton, "Score: ");
    SetButtonBackGroundPositions(&game->scoreButton, 1000, 500, 150, 75);
    SetButtonTextPositions(&game->scoreButton);
    game->scoreButtonColor.r = 0;
    game->scoreButtonColor.g = 0;
    game->scoreButtonColor.b = 0;
    game->scoreButtonColor.a = 255;

    game->score = 0;
    

    return 1;
}

int RenderGameScreen(SDL_Renderer* renderer, const MouseCoordinate mouse, Game* game, TTF_Font* font) {

    SDL_SetRenderDrawColor(renderer, 188, 188, 188, 255); // set background to gray

    SDL_RenderClear(renderer);

    for (int i = 0; i < game->gameButtonsSize; i++) {

        SDL_Rect copy = game->gameButtons[i].buttonBackGround;

        SDL_SetRenderDrawColor(renderer, game->map[i].color.r, game->map[i].color.g, 
            game->map[i].color.b, game->map[i].color.a);
        SDL_RenderFillRect(renderer, &copy);

    }


    char scoreText [40];

    sprintf(scoreText, "Score: %d", game->score);

    // show score at some side
    SetButton(&game->scoreButton, scoreText);
    RenderButton(renderer, font, &game->scoreButton, game->scoreButtonColor);

    SDL_RenderPresent(renderer);

    return 1;
}
