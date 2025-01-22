#include "input.h"

#include "game.h"


int ProcessKeyboardInput(SDL_Event* ev, Game* game) {

    printf("KEY: %d STATE:%d \n", ev->key.keysym.scancode, game->gameState);

    switch (ev->key.keysym.scancode) {
    
    case SDL_SCANCODE_ESCAPE:
    case SDL_SCANCODE_Q:
        //if (gameState == GAME) {
        //    gameState = MENU;
        //    return 1;
        //}
        if (game->gameState == States_GAME) {
            game->gameState = States_MENU;
            return 1;
        }
        return 0;
        break;
    
    
    default:
        break;
    }

    return 1;

}

int ProcessMouseInput(SDL_Event* ev, Game* game) {

    game->mouseCoordinate.xClick = ev->button.x;
    game->mouseCoordinate.yClick = ev->button.y;

    return 1;
}
