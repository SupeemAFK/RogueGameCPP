#ifndef UI_H
#define UI_H

#include <iostream>
#include <string>
#include <string.h>
#include <locale.h>
#include <ncursesw/ncurses.h>
#include "../../assets/skull.h"

class Dungeon;
class Player;
class Inventory;

class GameUI {
    public:
        WINDOW* gameWin;
        WINDOW* uiWin;

        GameUI(Dungeon* _dungeon, Player* _player, Inventory* _inventory);

        void initUI();
        void updateUI();
        void updateGameScreen();
        void drawDeathScreen();

    private:
        Dungeon* dungeon;
        Player* player;
        Inventory* inventory;

        void drawDungeon();
        void drawPlayerStatus();
        void drawDialogue(int startY);
        void drawPlayerControl(int startY);
};

#endif
