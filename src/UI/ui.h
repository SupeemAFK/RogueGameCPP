#ifndef UI_H
#define UI_H

#include <iostream>
#include <string>
#include <string.h>
#include <locale.h>
#include <ncursesw/ncurses.h>
#include "../../assets/skull.h"

class GameManager;

class GameUI {
    public:
        WINDOW* gameWin;
        WINDOW* uiWin;

        GameUI(GameManager* _gm);

        void initUI();
        void updateUI();
        void updateGameScreen();
        void drawDeathScreen();

    private:
        GameManager* gm;

        void drawDungeon();
        void drawPlayerStatus();
        void drawDialogue(int startY);
        void drawPlayerControl(int startY);
};

#endif
