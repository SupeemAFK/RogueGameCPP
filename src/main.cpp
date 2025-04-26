#include "./dungeon/dungeon.h"
#include "./UI/ui.h"
#include "./player/player.h"
#include <ctime>

int main() {
    srand(time(0));

    //Start
    generateDungeon();
    randomSpawnPlayer();
    initUI();
    drawDungeon(gameWin);
    updateUI();


    //Update
    int ch;
    while (true) {
        ch = getch();
        if (ch == 'q' || ch == 'Q') {
            break;
        }
        //Restart
        else if (ch == 'r' || ch == 'R') {
            generateDungeon();
            clearPlayer();
            randomSpawnPlayer();
        }
        else if (ch == 'w' || ch == 'W') {
            movePlayer({ 0, -1 });
        }
        else if (ch == 's' || ch == 'S') {
            movePlayer({ 0, 1 });
        }
        else if (ch == 'a' || ch == 'A') {
            movePlayer({ -1, 0 });
        }
        else if (ch == 'd' || ch == 'D') {
            movePlayer({ 1, 0 });
        }

        werase(gameWin);
        box(gameWin, 0, 0);
        drawDungeon(gameWin);
        updateUI();
    }

    //End ncurses
    endwin();
}