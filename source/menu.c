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

void SetButtonTextPositions(Button* button, int x, int y) {
    button->buttonText.x = x;
    button->buttonText.y = y;
}


void RenderButton(SDL_Renderer* renderer, TTF_Font* font, Button* button, 
    GameMenu menu, SDL_Texture* mainTexture, SDL_Surface* surface, SDL_Texture* texture) {


    surface = TTF_RenderText_Solid(font, button->text, menu.textColor);
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    if (!surface || !texture) {
        PRINT_ERROR_MSG;
        return;
    }

    // Get the dimensions of the text texture
    int textHeight, textWidth;
    SDL_QueryTexture(texture, NULL, NULL, &textWidth, &textHeight);

    SDL_RenderCopy(renderer, mainTexture, NULL, NULL);

    // add set start game rectangle
    SDL_RenderFillRect(renderer, &button->buttonBackGround);

    button->buttonText.w = textWidth;
    button->buttonText.h = textHeight;
    SDL_RenderCopy(renderer, texture, NULL, &button->buttonText);
    
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);


}

