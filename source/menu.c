#include "menu.h"



void SetButton(Button* button, char* text) {
    strcpy(button->text, text);
}

void SetButtonBackGroundPositions(Button* button, int x, int y, int w, int h) {
    button->buttonBackGround.x = x;
    button->buttonBackGround.y = y;
    button->buttonBackGround.w = w;
    button->buttonBackGround.h = h;
}

void SetButtonTextPositions(Button* button) {
    button->buttonText.x = button->buttonBackGround.x + 50;
    button->buttonText.y = button->buttonBackGround.y + 50;
    button->buttonText.w = (int)button->buttonBackGround.w * 0.4;
    button->buttonText.h = (int)button->buttonBackGround.h * 0.4;
}




void RenderButton(SDL_Renderer* renderer, TTF_Font* font, Button* button) {


    SDL_SetRenderDrawColor(renderer, 128, 0, 128, 255); // set background to purple
    SDL_RenderFillRect(renderer, &button->buttonBackGround);

    SDL_Color color = {153, 153, 153, 255};


    SDL_Surface* surface = TTF_RenderText_Solid(font, button->text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    if (!surface || !texture) {
        PRINT_ERROR_MSG;
        return;
    }

    SDL_RenderCopy(renderer, texture, NULL, &button->buttonText);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

}

