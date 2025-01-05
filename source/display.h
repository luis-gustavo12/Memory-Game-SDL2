#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "input.h"


typedef struct Button {

    SDL_Rect buttonBackGround;
    SDL_Rect buttonText;
    char text[128];

} Button;




void SetButton(Button* button, char* text);

void SetButtonBackGroundPositions(Button* button, int x, int y, int w, int h);

void SetButtonTextPositions(Button* button);

void RenderButton(SDL_Renderer* renderer, TTF_Font* font, Button* button);

int ClickedInside(const MouseCoordinate mouse, const Button button);