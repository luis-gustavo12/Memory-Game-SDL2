#pragma once


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "input.h"
#include "display.h"
#include "menu.h"
#include "game.h"
#include "log.h"

// defines
#define PRINT_ERROR_MSG printf("ERROR %d: [%s]\n", __LINE__ , SDL_GetError())
#define TRACE_FILE "memory_game.log"


// structs









// variables



// functions

int Init();
int SetObjects();
int CleanAndExit();
