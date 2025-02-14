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
#include "stdbool.h"
#include "display.h"
#include "log.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#ifdef WINDOWS
#pragma warning(disable : 4820)
#endif // WINDOWS


typedef enum {
    GameLogicState_None,     /* Neutral state */
    GameLogicState_Guessing, /* State where you'll be trying to guess the squares you've hit on the past*/
    GameLogicState_Filling,  /* State where you'll be clicking on the squares and putting them on the queue */
    GameLogicState_Awaiting, /* A substate of guessing, when you expect the user to guess the other square */
    GameLogicState_GameOver,
} GameLogicState;

typedef struct GameOverScreen {

    Button playAgainButton;
    Button exitButton;


}GameOverScreen;


typedef struct {
    int xClick;
    int yClick;
} MouseCoordinate;

/// @brief This is the map that holds a color as one key, and a button the value
typedef struct GameButtonsMap {

    SDL_Color color;
    SDL_Rect rectangle;
    char squareColorName [32];
    struct GameButtonsMap* next; // NOTE: this part is only important when setting the queue.

} GameButtonsMap;






typedef struct MemoryQueue {

    GameButtonsMap* first;
    GameButtonsMap* last;
    int size;

} MemoryQueue;

typedef enum {
    States_MENU,
    States_GAME,
    States_EXIT,
} States;

typedef struct Game {

    // GRAPHICAL
    Button gameButtons[60]; // Holds all the squares. game.h will also have its own buttons
    GameButtonsMap map[6];
    int gameButtonsSize;
    int score;
    Button scoreButton;
    TTF_Font* scoreButtonFont;
    SDL_Color scoreButtonColor;
    MemoryQueue* memoryQueue;
    int guessingCount;
    MemoryQueue* guessingQueue;
    int stackSize;
    States gameState;
    GameLogicState gameLogicState;
    Button gameLogicStateButton;
    SDL_Color gameLogicStateButtonColor;
    int attemptHits; // For every time in guessing state, we need to mark how many of the attemps it hit
    GameOverScreen gameOver;
    MouseCoordinate mouseCoordinate;

} Game;






/// @brief Initialize the game struct
/// @param game 
/// @return 1 for success
Game* InitGame(void);

/// @brief Renders the squares on the screen
/// @param renderer Rendering context
/// @param mouse The X and Y mouse Coordinates
/// @param game Game struct
/// @param font The font. Needed for displaying the score
void RenderGameScreen(SDL_Renderer* renderer, Game* game, TTF_Font* font);

void ProcessGameLogic(Game* game);

int HasHitSquare(const MouseCoordinate mouse, GameButtonsMap map);



/* QUEUE RELATED OPERATIONS */

void Enqueue(MemoryQueue* queue, GameButtonsMap* map);

GameButtonsMap* GetMap(MemoryQueue* queue, int index);

MemoryQueue* InitQueue(void);

void ResetQueue(MemoryQueue* queue);

/* QUEUE RELATED OPERATIONS -> END*/

void ResetGame(Game* game);

// Checks if the user square input is correct compared to MemoryQueue map
int CheckSquareOrderOnQueue(Game* game);

int ColorsAreEqual(SDL_Color color1, SDL_Color color2);

void RenderGameOverScreen(SDL_Renderer* renderer, const MouseCoordinate mouse, Game* game, TTF_Font* font);

/// @brief Checks the click coordinates matches the button coordinates
/// @param mouse The X and |Y mouse coordinates
/// @param button The button which you want to check
/// @return 1 if click was inside, 0 if click was outside
int ClickedInside(Game* game, const Button button);

void ProcessGameOver(Game* game);

int HasHitButton(MouseCoordinate mouse, Button button);

void DebugStack(Game* game);
