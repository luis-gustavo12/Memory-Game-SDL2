#pragma once


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "input.h"


#define PRINT_ERROR_MSG printf("ERROR %d: [%s]\n", __LINE__ ,SDL_GetError())


// defines


#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720


// structs


typedef enum STATES {
    MENU,
    GAME
} STATES;



// variables


extern enum STATES gameState;


// functions

int Init();
int SetObjects();
