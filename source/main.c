#include "main.h"

int running;
SDL_Window* window = NULL;
SDL_Renderer* mainRenderer = NULL; // main renderer
TTF_Font* font = NULL;
SDL_Color textColor = {188, 188, 188};
SDL_Event ev;
int txtWidth, txtHeight;
SDL_Rect rect;
GameMenu menu;


#ifndef REFACTOR
void renderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y) {
    SDL_Color color = {255, 255, 255}; // White color
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    int textWidth = surface->w;
    int textHeight = surface->h;

    SDL_Rect textRect = {x + (100 - textWidth) / 2, y + (50 - textHeight) / 2, textWidth, textHeight};
    SDL_RenderCopy(renderer, texture, NULL, &textRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}
#endif



int Init() {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        PRINT_ERROR_MSG;
        return -1;
    }

    if (TTF_Init()) {
        PRINT_ERROR_MSG;
        return -1;
    }


    return 1;
}


int SetObjects() {

    SDL_Surface* surface = NULL;

    window = SDL_CreateWindow(
        "Memory Game",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN);

    if (!window) {
        PRINT_ERROR_MSG;
        SDL_Quit();
        return -1;
    }

    mainRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!mainRenderer) {
        PRINT_ERROR_MSG;
        return -1;
    }

    



    return 1;

}

/// @brief Initialize external stuff, like text (ttf), images, etc
/// @return 1 for sucess, 0 or -1 for error
int InitExternalMedia() {

    font = TTF_OpenFont("media/fonts/OpenSans.ttf", 24);

    if (!font) {
        return -1;
    }

    return 1;

}



int main(int argc, char* argv[]) {


    if (Init() <= 0) exit(-1);

    if (SetObjects() <= 0) exit(-1);

    if (InitExternalMedia() <= 0) exit(-1);

    running = true;
    enum STATES gameState = MENU;



    // main loop
    while (running) {

        while ( SDL_PollEvent( &ev ) != 0 ) {

            // process input
            switch (ev.type) {

            case SDL_QUIT: 
                printf("QUIT CALLED!!\n");
                running = false;
                continue;

            case SDL_MOUSEBUTTONUP:
                //ProcessMouseInput(ev, renderer, rect);
                break;

            case SDL_KEYDOWN:
                break;

            }

        } // SDL_PollEvent( &ev )

        // display 
        

        switch (gameState) {
        case MENU: {

            Button startGameButton;
            Button exitButton;

            // set background color to green -> 115, 214, 71
            SDL_SetRenderDrawColor(mainRenderer, 115, 214, 71, 255);

            SDL_RenderClear(mainRenderer);

            SetButton(&startGameButton, "Start Game");
            SetButtonBackGroundPositions(&startGameButton, 150, 200, 375, 150);
            SetButtonTextPositions(&startGameButton);
            RenderButton(mainRenderer, font, &startGameButton);

            /////////////////////////////////////////////////////////////////////////////////

            SetButton(&exitButton, "Exit Game");
            SetButtonBackGroundPositions(&exitButton, 150, 500, 375, 150);
            SetButtonTextPositions(&exitButton);
            RenderButton(mainRenderer, font, &exitButton);

            SDL_RenderPresent(mainRenderer);

            break;

        } // case MENU
        
        case GAME:
            // display game
            break;

        default:
            break;
        }

        

        SDL_Delay(50);


        

    } //while (running)

    

    SDL_DestroyRenderer(mainRenderer);
    TTF_CloseFont(font);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();


    return 0;
}








