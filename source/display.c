#include "display.h"





void SetButton(Button* button, char* text) {
    if (text != NULL) strcpy(button->text, text);
    else memset(button->text, 0, sizeof(button->text));
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


void RenderButton(SDL_Renderer* renderer, TTF_Font* font, Button* button, SDL_Color color) {


    SDL_SetRenderDrawColor(renderer, 128, 0, 128, 255); // set background to purple
    SDL_RenderFillRect(renderer, &button->buttonBackGround);

    



    SDL_Surface* surface = TTF_RenderText_Solid(font, button->text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    if (!surface || !texture) {
        return;
    }

    SDL_RenderCopy(renderer, texture, NULL, &button->buttonText);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

}

int ClickedInside(const MouseCoordinate mouse, const Button button) {
    
    SDL_Rect rect = button.buttonBackGround;

    rect.h += rect.y;
    rect.w += rect.x;

    return ( ( mouse.xClick >= rect.x && mouse.yClick >= rect.y ) && ( mouse.yClick <= rect.h && mouse.xClick <= rect.w ) );

}

void SetButtonByColorSDL(Button* button, SDL_Rect rect) {
    button->buttonBackGround.x = rect.x;
    button->buttonBackGround.y = rect.y;
    button->buttonBackGround.w = rect.w;
    button->buttonBackGround.h = rect.h;
}

