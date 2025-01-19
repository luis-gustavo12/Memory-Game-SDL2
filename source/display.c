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

    SDL_RenderPresent(renderer);

    SDL_Surface* surface = TTF_RenderText_Solid(font, button->text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    if (!surface || !texture) {
        return;
    }

    SDL_RenderCopy(renderer, texture, NULL, &button->buttonText);

    SDL_RenderPresent(renderer);

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

void SetColorByValue(SDL_Color* color, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    color->r = r;
    color->g = g;
    color->b = b;
    color->a = a;
}

void SetButtonTextPositionsByValue(Button* button, int x, int y, int w, int h) {
    button->buttonText.x = x;
    button->buttonText.y = y;
    button->buttonText.h = h;
    button->buttonText.w = w;
}

void SetButtonName(Button *button, char *name) {
    strcpy(button->name, name);
}

void SetButtonBackgroundColorByValue(Button* button, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    button->colorButtonBackground.r = r;
    button->colorButtonBackground.g = g;
    button->colorButtonBackground.b = b;
    button->colorButtonBackground.a = a;
}

void RenderButtonEx(SDL_Renderer* renderer, TTF_Font* font, Button* button) {
    
    SDL_Color desiredColor = button->colorButtonBackground;
    
    SDL_SetRenderDrawColor(renderer, desiredColor.r, desiredColor.g, desiredColor.b, desiredColor.a); // set background to desired color
    SDL_RenderFillRect(renderer, &button->buttonBackGround);

    SDL_Color bgColor = {0, 0, 0, 255 };

    SDL_Surface* surface = TTF_RenderText_Solid(font, button->text, bgColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    if (!surface || !texture) {
        return;
    }

    SDL_RenderCopy(renderer, texture, NULL, &button->buttonText);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void SetButtonTextColorByValue(Button* button, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    button->colorButtonText.r = r;
    button->colorButtonText.b = b;
    button->colorButtonText.g = g;
    button->colorButtonText.a = a;
}
