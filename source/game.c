#include "game.h"


SDL_Color gameColors[4] = {
    {204, 0, 0, 255},     // RED
    {41, 134 ,204, 255},  // BLUE
    {255, 217, 102, 255}, // YELLOW
    {106, 168, 79, 255}   // GREEN
};


// Each button will be represented by one of gameColors
SDL_Rect gameButtonsBackground[4] = {

    {50, 50, 150, 150},
    {50, 100, 150, 150},
    {100, 50, 150, 150},
    {100, 100, 150, 150}

};


int InitGame(Game* game) {

    

    // The idea in the game is basically have buttons for colors. By now, we will choose 4,
    // but in the future, the idea is to have some kind of dificulty in it.


    // fill Game struct
    for (int i = 0; i < 4; i++) {

        Button btn;

        SetButton(&btn, NULL);

        SetButtonByColorSDL(&btn, gameButtonsBackground[i]);

        game->gameButtons[i] = btn;
        game->map->color = gameColors[i];
        game->map->rectangle = gameButtonsBackground[i];

    }

    return 1;
}
