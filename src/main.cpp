#include "./dungeon/dungeon.h"
#include "./UI/ui.h"
#include "./player/player.h"
#include "./coin/coin.h"
#include "./nextLevel/nextLevel.h"
#include "./gameManager/gameManager.h"
#include <ctime>
#include <iostream>

int main() {
    srand(time(0));

    //Start
    Dungeon dungeon;
    Coin coin(dungeon);
    NextLevel nextLevelDoor(dungeon);
    Player player(dungeon, coin, nextLevelDoor, 100);
    GameManager gameManager(dungeon, coin, nextLevelDoor, player);
    GameUI ui(dungeon, player);

    gameManager.startGame();
    ui.initUI();
    ui.updateGameScreen();
    ui.updateUI();

    //Update
    int ch;
    while (true) {
        ch = getch();
        if (ch == 'q' || ch == 'Q') {
            break;
        }
        //Restart
        else if (ch == 'r' || ch == 'R') {
            gameManager.restartGame();
        }
        else if (ch == 'w' || ch == 'W') {
            player.movePlayer({ 0, -1 });
        }
        else if (ch == 's' || ch == 'S') {
            player.movePlayer({ 0, 1 });
        }
        else if (ch == 'a' || ch == 'A') {
            player.movePlayer({ -1, 0 });
        }
        else if (ch == 'd' || ch == 'D') {
            player.movePlayer({ 1, 0 });
        }

        ui.updateGameScreen(); //Always update game screen
        ui.updateUI(); //Always update UI
    }

    //End ncurses
    endwin();
}