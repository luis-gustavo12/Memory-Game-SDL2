#include "main.h"

int running;
SDL_Window* window = NULL;
SDL_Renderer* mainRenderer = NULL; // main renderer
TTF_Font* font = NULL;
SDL_Color textColor = {188, 188, 188};
SDL_Texture* mainTexture; // main background texture
SDL_Event ev;
int txtWidth, txtHeight;
SDL_Rect rect;
GameMenu menu;



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

    


    surface = SDL_CreateRGBSurface(
        0, WINDOW_WIDTH, WINDOW_HEIGHT,
        32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);

    if (!surface) {
        PRINT_ERROR_MSG;
        SDL_Quit();
        return -1;
    }

    SDL_FillRect(surface, NULL, SDL_MapRGB(
        surface->format, 26,190,99
    ));

    mainTexture = SDL_CreateTextureFromSurface(mainRenderer, surface);

    if (!mainTexture) {
        PRINT_ERROR_MSG;
        SDL_Quit();
        return -1;
    }

    SDL_FreeSurface(surface);

    SDL_QueryTexture(mainTexture, NULL, NULL, &txtWidth, &txtHeight);

    rect.x = WINDOW_WIDTH / 3;
    rect.y = WINDOW_HEIGHT / 3;
    rect.w = txtWidth;
    rect.h = txtHeight;

    // set menu
    menu.textColor.r = 188;
    menu.textColor.g = 188;
    menu.textColor.b = 188;
    menu.textColor.a = 255;



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

            int textWidth, textHeight;
            SDL_Surface* surface;
            SDL_Texture* texture;
            Button startGameButton;
            Button exitButton;

            SDL_RenderClear(mainRenderer);

            // set to purple
            SDL_SetRenderDrawColor(mainRenderer, 128, 0, 128, 255);

            SetButton(&startGameButton, "Start Game");
            SetButtonBackGroundPositions(&startGameButton, 300, 200, 375, 150);
            SetButtonTextPositions(&startGameButton, 350, 275);
            RenderButton(mainRenderer, font, &startGameButton, menu, mainTexture, surface, texture);



            /////////////////////////////////////////////////////////////////////////////////


            SetButton(&exitButton, "Exit Game");
            SetButtonBackGroundPositions(&exitButton, 300, 500, 375, 150);
            SetButtonTextPositions(&exitButton, 350, 525);
            RenderButton(mainRenderer, font, &exitButton, menu, mainTexture, surface,texture);
            




            SDL_RenderPresent(mainRenderer);

            // display menu
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






    

    SDL_DestroyTexture(mainTexture);
    SDL_DestroyRenderer(mainRenderer);
    TTF_CloseFont(font);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();


    return 0;
}

/*






switch (gameState) {
        case MENU: {


            SDL_RenderClear(renderer);

            // start game button
            SDL_Surface *textSurface = TTF_RenderText_Solid(font, "Start Game", textColor);
            SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            // Get the dimensions of the text texture
            int textWidth, textHeight;
            SDL_QueryTexture(textTexture, NULL, NULL, &textWidth, &textHeight);


            // copy texture to the renderer
            SDL_RenderCopy(renderer, texture, NULL, NULL);

            // set color to purple
            SDL_SetRenderDrawColor(renderer, 128, 0, 128, 255);

            // add set start game rectangle
            SDL_Rect startGameButton = {300, 200, 200, 200};
            SDL_RenderFillRect(renderer, &startGameButton);

            SDL_Rect textStartGame = {350, 275, textWidth, textHeight};
            SDL_RenderCopy(renderer, textTexture, NULL, &textStartGame);

            // // quit game
            // textSurface = TTF_RenderText_Solid(font, "Quit Game", textColor);
            // textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

            // SDL_RenderClear(renderer);

            // // copy texture to the renderer
            // SDL_RenderCopy(renderer, texture, NULL, NULL);

            // SDL_QueryTexture(textTexture, NULL, NULL, &textWidth, &textHeight);


            // // quit game button
            // SDL_Rect quitGameButton = { 300, 400, 200, 200  };
            // SDL_RenderFillRect(renderer, &quitGameButton);
            // SDL_Rect textQuitGame = {350, 275, 200, 200 };
            // SDL_RenderCopy(renderer, texture, NULL, &textQuitGame);
            // SDL_RenderClear(renderer);
            // SDL_RenderPresent(renderer);

            // SDL_RenderClear(renderer);

            // display menu
            break;
        } // case MENU




*/