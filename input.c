#include "input.h"



void ProcessMouseInput(SDL_Event ev) {

    switch (ev.button.button) {

    case SDL_BUTTON_LEFT:

        printf("BUTTON LEFT!!\n");
        
        break;
    
    default:
        break;
    }


}
