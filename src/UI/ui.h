#ifndef UI_H
#define UI_H

#include <ncursesw/ncurses.h>
#include "../dungeon/dungeon.h"
#include "../player/player.h"

class GameUI {
    public:
        WINDOW* gameWin;
        WINDOW* uiWin;
        Dungeon& dungeon;
        Player& player;

        GameUI(Dungeon& _dungeon, Player& _player);

        void initUI();
        void drawDungeon();
        void drawPlayerStatus();
        void drawDialogue(int startY);
        void drawPlayerControl(int startY);
        void updateUI();
        void updateGameScreen();
};

#endif
