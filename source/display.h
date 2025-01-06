/**
 * @file display.h
 * @brief This module gets all the display related structs and standards.
 * @version 0.1
 * @date 2025-01-05
 * 
 * @copyright Copyright (c) 2025
 * 
 */


#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "input.h"
#include "states.h"


/// @brief Representation of a button on the screen, can be used anywhere as long as
/// display.h is included.
typedef struct Button {

    SDL_Rect buttonBackGround;
    SDL_Rect buttonText;
    char text[128];

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

/// @brief Checks the click coordinates matches the button coordinates
/// @param mouse The X and |Y mouse coordinates
/// @param button The button which you want to check
/// @return 1 if click was inside, 0 if click was outside
int ClickedInside(const MouseCoordinate mouse, const Button button);

/// @brief Set buttons positions given a SDL rect
/// @param button Button the to be changed
/// @param rect Rectangle whose atributes will be copied to button
void SetButtonByColorSDL(Button* button, SDL_Rect rect);