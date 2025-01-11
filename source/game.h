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


typedef enum {
    GameLogicState_None,     /* Neutral state */
    GameLogicState_Guessing, /* State where you'll be trying to guess the squares you've hit on the past*/
    GameLogicState_Filling,  /* State where you'll be clicking on the squares and putting them on the queue */
    GameLogicState_Awaiting, /* A substate of guessing, when you expect the user to guess the other square */
    GameLogicState_GameOver,
} GameLogicState;




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
    GameLogicState gameLogicState;
    Button gameLogicStateButton;
    SDL_Color gameLogicStateButtonColor;
    int attemptHits; // For every time in guessing state, we need to mark how many of the attemps it hit

} Game;


typedef struct GameOver {

    Button tryAgainButton;
    Button exitButton;


} GameOver;




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

int CheckMapInQueue(MemoryQueue queue, GameButtonsMap map, int stackSize);

int ColorsAreEqual(SDL_Color color1, SDL_Color color2);

void RenderGameOverScreen(SDL_Renderer* renderer, const MouseCoordinate mouse, Game* game, TTF_Font* font);
