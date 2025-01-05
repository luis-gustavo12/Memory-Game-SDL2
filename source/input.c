#include "input.h"




int ProcessKeyboard(SDL_Event* ev) {

    printf("KEY: %d\n", ev->key.keysym.scancode);

    switch (ev->key.keysym.scancode) {
    
    case SDL_SCANCODE_ESCAPE:
    case SDL_SCANCODE_Q:
        return 0;
        break;
    
    
    default:
        break;
    }

    return 1;

}

int ProcessMouse(SDL_Event* ev, MouseCoordinate* mouse) {

    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

    printf("CLICK PROCESS X: %d Y: %d\n", ev->button.x, ev->button.y);


    mouse->xClick = ev->button.x;
    mouse->yClick = ev->button.y;
    

    return 1;
}
