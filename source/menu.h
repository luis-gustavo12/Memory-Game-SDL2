#pragma once


#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "input.h"
#include "display.h"





typedef struct GameMenu {

    SDL_Color textColor; // text color

} GameMenu;



/// @brief Init the buttons for the menus. Better do it before the main loop
/// @param startBtn start button
/// @param exitBtn exit button
/// @return  1 for success, 0, for failure
int InitMenuButtons(Button* startBtn, Button* exitBtn);

