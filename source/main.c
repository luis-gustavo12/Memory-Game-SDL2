#include "main.h"

int running;
SDL_Window* window = NULL;
SDL_Renderer* mainRenderer = NULL; // main renderer
TTF_Font* font = NULL;
SDL_Color textColor = {188, 188, 188};
SDL_Event ev;
int txtWidth, txtHeight;
SDL_Rect rect;
GameMenu menu = {{153, 153, 153, 255}};
Game game;
//MouseCoordinate mouse; // this gets the current x and y coordinates when there's a click
bool enteredMenu = false;



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

int gameButtonsSize;

/// @brief Initialize external stuff, like text (ttf), images, etc
/// @return 1 for sucess, 0 or -1 for error
int InitExternalMedia() {

#ifdef LINUX
    font = TTF_OpenFont("../media/fonts/OpenSans.ttf", 24);
#elif WINDOWS
    font = TTF_OpenFont("..\\..\\..\\media\\fonts\\OpenSans.ttf", 24);
#endif
    if (!font) {
        return -1;
    }

    return 1;

}


int CleanAndExit() {

    if (mainRenderer != NULL) SDL_DestroyRenderer(mainRenderer);
    if (window != NULL) SDL_DestroyWindow(window);
    if (font != NULL) TTF_CloseFont(font);
    SDL_Quit();
    TTF_Quit();

    return -1;
}



int main(int argc, char* argv[]) {

    Button startGameButton;
    Button exitButton;

    if (Init() <= 0) exit(-1);

    if (SetObjects() <= 0) return CleanAndExit();

    if (InitExternalMedia() <= 0) return CleanAndExit();

    InitMenuButtons(&startGameButton, &exitButton);
    if (InitGame(&game) != 1) return CleanAndExit();

    running = true;
    game.gameState = States_MENU;
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
                printf("SDL_MOUSEBUTTONDOWN X: %d Y: %d\n",
                    ev.button.x, ev.button.y);
                inputType = MOUSE;
                ProcessMouseInput(&ev, &game);
                break;

            case SDL_KEYDOWN:
                inputType = KEYBOARD;
                if (ProcessKeyboardInput(&ev, &game) == false) {
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


        switch (game.gameState) {
        case States_MENU: {


            // set background color to green -> 115, 214, 71
            SDL_SetRenderDrawColor(mainRenderer, 115, 214, 71, 255);

            SDL_RenderClear(mainRenderer);

            RenderButton(mainRenderer, font, &startGameButton, menu.textColor);

            RenderButton(mainRenderer, font, &exitButton, menu.textColor);

            SDL_RenderPresent(mainRenderer);

            // menu only has buttons for now, so I'm checking the position of the click, one by one
            // In the future, either will be an array of buttons, or a va_list on the function
            // mark this as TODO: 

            if (inputType == MOUSE) {
                if (  ClickedInside(&game, startGameButton) ) {
                    game.gameState = States_GAME;
                    break;
                }


                if (ClickedInside(&game, exitButton) ) {
                    running = false;
                    break;
                }
                inputType = EMPTY;
            }

            enteredMenu = true;

            break;

        } // case MENU
        
        case States_GAME: {

            // this is the variable marker that checks if the game is going to be clicked
            // for a second time, since whenever you go into the game, you need to reboot it
            if (enteredMenu == true) {
                ResetGame(&game);
                enteredMenu = false;
            }

            RenderGameScreen(mainRenderer, &game, font);

            if (inputType == MOUSE) ProcessGameLogic(&game);

            break;

        }

        case States_EXIT:
            running = false;
            break;


        default:
            break;
        }

        
        if (inputType == MOUSE) {
            game.mouseCoordinate.xClick = -1;
            game.mouseCoordinate.yClick = -1;
        }

        inputType = EMPTY;

        SDL_Delay(50);



    } //while (running)

    

    SDL_DestroyRenderer(mainRenderer);
    TTF_CloseFont(font);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();


    return 0;
}



