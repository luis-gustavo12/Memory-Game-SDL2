#pragma once


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "input.h"


#define PRINT_ERROR_MSG printf("ERROR %d: [%s]\n", __LINE__ ,SDL_GetError())




// structs




// variables

int running = true;
SDL_Window* window = NULL;
SDL_Surface* surface = NULL;
SDL_Event ev;





// functions

int Init();
int SetObjects();
