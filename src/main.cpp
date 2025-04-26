#include "./dungeon/dungeon.h"
#include "./UI/ui.h"
#include <ctime>

int main() {
    srand(time(0));

    //Start
    generateDungeon();
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
        else if (ch == 'r' || ch == 'R') {
            generateDungeon();
        }

        werase(gameWin);
        box(gameWin, 0, 0);
        drawDungeon(gameWin);
        updateUI();
    }

    //End ncurses
    endwin();
}