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
    struct GameButtonsMap* next; // NOTE: this part is only important when setting the queue.

} GameButtonsMap;





typedef struct MemoryQueue {

    GameButtonsMap map [3000]; // Handles the squares that the user hit
    int size;
    GameButtonsMap* first;
    GameButtonsMap* last;

} MemoryQueue;

typedef struct Game {

    // GRAPHICAL
    Button gameButtons[60]; // Holds all the squares. game.h will also have its own buttons
    GameButtonsMap map[20];
    int gameButtonsSize;
    int score;
    Button scoreButton;
    TTF_Font* scoreButtonFont;
    SDL_Color scoreButtonColor;
    MemoryQueue memoryQueue;
    int stackSize;

} Game;







/// @brief Initialize the game struct
/// @param game 
/// @return 1 for success
int InitGame(Game* game);

/// @brief Renders the squares on the screen
/// @param renderer Rendering context
/// @param mouse The X and Y mouse Coordinates
/// @param game Game struct
/// @param font The font. Needed for displaying the score
void RenderGameScreen(SDL_Renderer* renderer, const MouseCoordinate mouse, Game* game, TTF_Font* font);

void ProcessGameLogic(Game* game, const MouseCoordinate mouse);

int HasHitSquare(const MouseCoordinate mouse, GameButtonsMap map);



/* QUEUE RELATED OPERATIONS */

void Enqueue(MemoryQueue* queue, GameButtonsMap* map);



/* QUEUE RELATED OPERATIONS -> END*/

void ResetGame(Game* game);