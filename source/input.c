#include "input.h"




int ProcessKeyboardInput(SDL_Event* ev) {

    printf("KEY: %d STATE:%d \n", ev->key.keysym.scancode, gameState);

    switch (ev->key.keysym.scancode) {
    
    case SDL_SCANCODE_ESCAPE:
    case SDL_SCANCODE_Q:
        if (gameState == GAME) {
            gameState = MENU;
            return 1;
        }
        return 0;
        break;
    
    
    default:
        break;
    }

    return 1;

}

int ProcessMouseInput(SDL_Event* ev, MouseCoordinate* mouse) {


    mouse->xClick = ev->button.x;
    mouse->yClick = ev->button.y;

    return 1;
}
