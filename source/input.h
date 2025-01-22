/**
 * @file input.h
 * @brief Module to handle all the input associated operation
 * @version 0.1
 * @date 2025-01-05
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once


#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "game.h"


// structs

typedef enum InputType {
    EMPTY,
    KEYBOARD,
    MOUSE
} InputType;




// variables


// functions

int ProcessKeyboardInput(SDL_Event* ev, Game* game);

int ProcessMouseInput(SDL_Event* ev, Game* game);

