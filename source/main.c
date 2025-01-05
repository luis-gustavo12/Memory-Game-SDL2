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
MouseCoordinate mouse; // this gets the current x and y coordinates when there's a click




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

    Button startGameButton;
    Button exitButton;

    if (Init() <= 0) exit(-1);

    if (SetObjects() <= 0) exit(-1);

    if (InitExternalMedia() <= 0) exit(-1);


    // setting menu buttons. Moved from main display display switch case
    SetButton(&startGameButton, "Start Game");
    SetButtonBackGroundPositions(&startGameButton, 150, 200, 375, 150);
    SetButtonTextPositions(&startGameButton);

    SetButton(&exitButton, "Exit Game");
    SetButtonBackGroundPositions(&exitButton, 150, 500, 375, 150);
    SetButtonTextPositions(&exitButton);



    running = true;
    States gameState = MENU;
    bool skip = 0;
    InputType inputType = EMPTY;


    // main loop
    while (running) {

        while ( SDL_PollEvent( &ev ) != 0 ) {


            // process input
            switch (ev.type) {

            case SDL_QUIT: 
                printf("QUIT CALLED!!\n");
                running = false;
                continue;

            case SDL_MOUSEBUTTONDOWN:
                printf("SDL_MOUSEBUTTONDOWN\n");
                inputType = MOUSE;
                ProcessMouse(&ev, &mouse);
                break;

            case SDL_KEYDOWN:
                inputType = KEYBOARD;
                if (ProcessKeyboard(&ev) == false) {
                    running = false;
                    skip = true;
                }
                
                break;

            }

        } // SDL_PollEvent( &ev )

        // display use this file's times instead of current time

        
        if (skip) {
            skip = false;
            continue;
        }


        switch (gameState) {
        case MENU: {

            // set background color to green -> 115, 214, 71
            SDL_SetRenderDrawColor(mainRenderer, 115, 214, 71, 255);

            SDL_RenderClear(mainRenderer);

            RenderButton(mainRenderer, font, &startGameButton);



            RenderButton(mainRenderer, font, &exitButton);

            SDL_RenderPresent(mainRenderer);

            // menu only has buttons for now, so I'm checking the position of the click, one by one
            // In the future, either will be an array of buttons, or a va_list on the function
            // mark this as TODO: 

            if (inputType == MOUSE) {
                if (  ClickedInside(mouse, startGameButton) ) {
                    gameState = GAME;
                    break;
                } 


                if (ClickedInside(mouse, exitButton) ) {
                    running = false;
                    break;
                }
                inputType = EMPTY;
            }


            break;

        } // case MENU
        
        case GAME: {
            printf("GAME GAME GAME\n");

            SDL_RenderClear(mainRenderer);

            SDL_SetRenderDrawColor(mainRenderer, 188, 188, 188, 255);

            SDL_RenderPresent(mainRenderer);

            break;

        }

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








