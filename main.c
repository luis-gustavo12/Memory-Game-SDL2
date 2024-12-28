#include "main.h"

int Init() {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        PRINT_ERROR_MSG;
        return -1;
    }


    return 1;
}


int SetObjects() {

    window = SDL_CreateWindow(
        "Memory Game",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        640, 480,
        SDL_WINDOW_SHOWN);

    if (!window) {
        PRINT_ERROR_MSG;
        SDL_Quit();
        return -1;
    }

    surface = SDL_GetWindowSurface(window);

    if (!surface) {
        PRINT_ERROR_MSG;
        return -1;
    }

    if ( SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 90, 120)  )  < 0 ) {
        PRINT_ERROR_MSG;
        return -1;
    }

    SDL_UpdateWindowSurface(window);

    return 1;

}



int main(int argc, char* argv[]) {


    if (Init() <= 0) exit(-1);

    if (SetObjects() <= 0) exit(-1);

    while (running) {

        while ( SDL_PollEvent( &ev ) != 0 ) {

            switch (ev.type) {

                case SDL_QUIT: 

                    printf("QUIT CALLED!!\n");
                    exit(-1);
                    break;
                

                case SDL_MOUSEBUTTONUP:
                    ProcessMouseInput(ev);
                    break;

                default:
                    break;

            }


        }


        SDL_Delay(100);

    }
    


    SDL_DestroyWindow(window);
    SDL_Quit();


    return 0;
}