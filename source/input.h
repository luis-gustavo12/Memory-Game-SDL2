#pragma once


#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>


// structs


typedef struct {
    int xClick;
    int yClick;
} MouseCoordinate;

// variables


// functions

int ProcessKeyboardInput(SDL_Event* ev);

int ProcessMouseInput(SDL_Event* ev, MouseCoordinate* mouse);

