/**
 * @file game.h
 * @brief Modules that handles all the stuff related to the main game logic, including input, display
 * @version 0.1
 * @date 2025-01-05
 * 
 * @copyright Copyright (c) 2025
 * 
 */


#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "display.h"
#include "input.h"
#include "main.h"
#include "states.h"



/// @brief This is the map that holds a color as one key, and a button the value
typedef struct GameButtonsMap {

    SDL_Color color;
    SDL_Rect rectangle;

} GameButtonsMap;





typedef struct Game {

    // GRAPHICAL
    Button gameButtons [60]; // game.h will also have your own buttons
    GameButtonsMap map [20];
    int score;
    int gameButtonsSize;
    Button scoreButton;
    TTF_Font* scoreButtonFont;
    SDL_Color scoreButtonColor;
    

} Game;

/// @brief Initialize the game struct
/// @param game 
/// @return 1 for success
int InitGame(Game* game);

int RenderGameScreen(SDL_Renderer* renderer, const MouseCoordinate mouse, Game* game, TTF_Font* font);