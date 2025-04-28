#ifndef UI_H
#define UI_H

#include <iostream>
#include <string>
#include <string.h>
#include <locale.h>
#include <ncursesw/ncurses.h>
#include "../dungeon/dungeon.h"
#include "../player/player.h"
#include "../../assets/skull.h"

class GameUI {
    public:
        WINDOW* gameWin;
        WINDOW* uiWin;
        Dungeon& dungeon;
        Player& player;

        GameUI(Dungeon& _dungeon, Player& _player);

        void initUI();
        void updateUI();
        void updateGameScreen();
        void drawDeathScreen();

    private:
        void drawDungeon();
        void drawPlayerStatus();
        void drawDialogue(int startY);
        void drawPlayerControl(int startY);
};

#endif
