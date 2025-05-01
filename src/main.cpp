#include "./dungeon/dungeon.h"
#include "./UI/ui.h"
#include "./player/player.h"
#include "./enemy/enemy.h"
#include "./coin/coin.h"
#include "./nextLevel/nextLevel.h"
#include "./gameManager/gameManager.h"
#include <ctime>
#include <iostream>

int main() {
    srand(time(0));

    //Start
    GameManager gameManager;
    GameUI ui(&gameManager.dungeon, &gameManager.player, &gameManager.inventory);

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
            if (gameManager.player.die) gameManager.player.die = false;
            gameManager.restartGame();
        }
        else if ((ch == 'w' || ch == 'W') && !gameManager.player.die) {
            gameManager.player.movePlayer({ 0, -1 });
            for (auto& enemy : gameManager.enemies) {
                enemy->randomMoveMonster();
                enemy->checkNextToPlayer();
            }
        }
        else if ((ch == 's' || ch == 'S') && !gameManager.player.die) {
            gameManager.player.movePlayer({ 0, 1 });
            for (auto& enemy : gameManager.enemies) {
                enemy->randomMoveMonster();
                enemy->checkNextToPlayer();
            }
        }
        else if ((ch == 'a' || ch == 'A') && !gameManager.player.die) {
            gameManager.player.movePlayer({ -1, 0 });
            for (auto& enemy : gameManager.enemies) {
                enemy->randomMoveMonster();
                enemy->checkNextToPlayer();
            }
        }
        else if ((ch == 'd' || ch == 'D') && !gameManager.player.die) {
            gameManager.player.movePlayer({ 1, 0 });
            for (auto& enemy : gameManager.enemies) {
                enemy->randomMoveMonster();
                enemy->checkNextToPlayer();
            }
        }
        else if (ch == '1' && !gameManager.player.die) {
            gameManager.inventory.useItem(0);
        }
        else if (ch == '2' && !gameManager.player.die) {
            gameManager.inventory.useItem(1);
        }
        else if (ch == '3' && !gameManager.player.die) {
            gameManager.inventory.useItem(2);
        }
        else if (ch == '4' && !gameManager.player.die) {
            gameManager.inventory.useItem(3);
        }
        else if (ch == '5' && !gameManager.player.die) {
            gameManager.inventory.useItem(4);
        }

        if (gameManager.player.die) {
            ui.drawDeathScreen();
        }
        else {
            ui.updateGameScreen(); //Always update game screen
            ui.updateUI(); //Always update UI
        }
    }

    //End ncurses
    endwin();
}