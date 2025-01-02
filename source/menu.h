#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "main.h"
#include "input.h"



typedef struct Button {

    SDL_Rect buttonBackGround;
    SDL_Rect buttonText;
    char text [128];
    

} Button;


typedef struct GameMenu {

    SDL_Color textColor; // text color
    Uint8 colors[3]; // button background color
    Button buttons [10];
    int buttonsSize;

} GameMenu;


void SetButton(Button* button, char* text);

void SetButtonBackGroundPositions(Button *button, int x, int y, int w, int h);

void SetButtonTextPositions(Button* button, int x, int y);

void RenderButton(SDL_Renderer* renderer, TTF_Font* font, Button* button, GameMenu menu, SDL_Texture* mainTexture, SDL_Surface* surface, SDL_Texture* texture);


