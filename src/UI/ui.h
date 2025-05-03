#ifndef UI_H
#define UI_H

#include <iostream>
#include <string>
#include <string.h>
#include <locale.h>
#include <thread>    
#include <mutex>    
#include <atomic> 
#include <chrono>
#include <vector>
#include <ncursesw/ncurses.h>
#include "../../assets/skull.h"

using namespace std;

class GameManager;

struct TimedLog {
    string text;
    chrono::steady_clock::time_point timestamp;
};

class GameUI {
    public:
        GameUI(GameManager* _gm);

        void initUI();
        void updateUI();
        void updateGameScreen();
        void drawDeathScreen();
        void addLog(string text);

    private:
        GameManager* gm;
        WINDOW* gameWin;
        WINDOW* uiWin;

        vector<TimedLog> logs;
        mutex logMutex;

        void drawDungeon();
        void drawPlayerStatus();
        void drawDialogue(int startY);
        void drawPlayerControl(int startY);
};

#endif
