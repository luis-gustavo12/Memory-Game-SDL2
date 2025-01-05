#include "menu.h"

int InitMenuButtons(Button* startBtn, Button* exitBtn) {
    // setting menu buttons. Moved from main display display switch case
    SetButton(startBtn, "Start Game");
    SetButtonBackGroundPositions(startBtn, 150, 200, 375, 150);
    SetButtonTextPositions(startBtn);

    SetButton(exitBtn, "Exit Game");
    SetButtonBackGroundPositions(exitBtn, 150, 500, 375, 150);
    SetButtonTextPositions(exitBtn);

    return 1;
}




