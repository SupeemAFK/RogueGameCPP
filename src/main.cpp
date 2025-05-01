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