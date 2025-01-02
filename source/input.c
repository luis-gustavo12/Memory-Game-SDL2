#include "input.h"

enum STATES gameState;





void ProcessMouseInput(SDL_Event ev, SDL_Renderer* renderer, SDL_Rect rect) {

    int state = ev.motion.state;

    printf("X: %d    Y: %d\n", ev.motion.x, ev.motion.y);

    switch (ev.button.button) {

    case SDL_BUTTON_LEFT:

        printf("BUTTON LEFT!!\n");
        printf("RECT H: %d WIDTH: %d X: %d Y: %d\n", rect.h,
            rect.w, rect.x, rect.y);


        switch (gameState) {
        case MENU:
            
            printf("MENU\n");

            break;

        case GAME:


            break;
        
        default:
            break;
        }
        
        
        break;
    
    default:
        break;
    }
}
