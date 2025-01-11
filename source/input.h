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

#ifdef LINUX
#include <SDL2/SDL.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include "states.h"

// structs

typedef enum InputType {
    EMPTY,
    KEYBOARD,
    MOUSE
} InputType;


typedef struct {
    int xClick;
    int yClick;
} MouseCoordinate;

// variables


// functions

int ProcessKeyboardInput(SDL_Event* ev);

int ProcessMouseInput(SDL_Event* ev, MouseCoordinate* mouse);

