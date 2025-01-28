/**
 * @file display.h
 * @brief This module gets all the display related structs and standards.
 * @version 0.1
 * @date 2025-01-05
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#define COLOR_NAME_RED "RED"
#define COLOR_NAME_YELLOW "YELLOW"
#define COLOR_NAME_BLUE "BLUE"
#define COLOR_NAME_GREEN "GREEN"

#define COLOR_VALUE_RED 1



#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"


/// @brief Representation of a button on the screen, can be used anywhere as long as
/// display.h is included.
typedef struct Button {

    SDL_Rect buttonBackGround;
    SDL_Rect buttonText;
    SDL_Color colorButtonBackground;
    SDL_Color colorButtonText;
    char text[128];
    char name[128]; // A name for what the buttons represent. Ideally for the squares on the game

} Button;




/// @brief Sets the button a text
/// @param button The button you want to display
/// @param text The text that will be displayed on the screen
void SetButton(Button* button, char* text);

/// @brief Set the x, y, width and height coordinates of the button
/// @param button The button you want to set
/// @param x X coordinate
/// @param y Y coordinate
/// @param w Width
/// @param h Height
void SetButtonBackGroundPositions(Button* button, int x, int y, int w, int h);

/// @brief Set the text positions for the text automatically, since it needs to be smaller than the button background
// metrics, or it will look weird
/// @param button 
void SetButtonTextPositions(Button* button);

/// @brief Renders the button to the screen
/// @param renderer The renderer to which the button will be displayed
/// @param font The font that will display the text in the text rectangle
/// @param button The button to be displayed
/// @param color The color in which you want to pass
void RenderButton(SDL_Renderer* renderer, TTF_Font* font, Button* button, SDL_Color color);



/// @brief Set buttons positions given a SDL rect
/// @param button Button the to be changed
/// @param rect Rectangle whose atributes will be copied to button
void SetButtonByColorSDL(Button* button, SDL_Rect rect);

/// @brief Set SDL_Color object given rgb
/// @param color 
void SetColorByValue(SDL_Color* color, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

/// @brief Set The text of the button positions given the coordinates
void SetButtonTextPositionsByValue(Button* button, int x, int y, int w, int h);

/// @brief Set a name for the button, kind of a secondary text
/// @param button the button object
void SetButtonName(Button* button, char* name);

/// @brief Set the color of the background, given rgba values
/// @param button the button object
void SetButtonBackgroundColorByValue(Button* button, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

/// @brief Render button on the screen given the coordinates
/// @param renderer the rendering context
void RenderButtonEx(SDL_Renderer* renderer, TTF_Font* font, Button* button);

/// @brief Set the color of the text given its value
void SetButtonTextColorByValue(Button* button, Uint8 r, Uint8 g, Uint8 b, Uint8 a);