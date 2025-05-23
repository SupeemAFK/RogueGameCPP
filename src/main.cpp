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

    gameManager.startGame();
    gameManager.ui.initUI();
    gameManager.ui.updateGameScreen();
    gameManager.ui.updateUI();

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
        else if ((ch == 'e' || ch == 'E') && !gameManager.player.die) {
            gameManager.inventory.useItem(gameManager.getNumItem() - 1);
        }
        else if ((ch == 'c' || ch == 'C') && !gameManager.player.die) {
            Item* item = gameManager.inventory.getInventoryKeys()[gameManager.getNumItem() - 1];
            gameManager.inventory.discardItemFromInventory(item);
        }
        else if ((ch == 'v' || ch == 'V') && !gameManager.player.die) {
            if (gameManager.player.getPlayerWeapon() != nullopt) {
                bool success = gameManager.inventory.addItemToInventory(new Weapon(*gameManager.player.getPlayerWeapon()));
                if (success) gameManager.player.removeWeapon();
            }
        }
        else if ((ch == 'b' || ch == 'B') && !gameManager.player.die) {
            gameManager.player.removeWeapon();
        }
        else if (ch == '1' && !gameManager.player.die) {
            gameManager.setNumItem(1);
        }
        else if (ch == '2' && !gameManager.player.die) {
            gameManager.setNumItem(2);
        }
        else if (ch == '3' && !gameManager.player.die) {
            gameManager.setNumItem(3);
        }
        else if (ch == '4' && !gameManager.player.die) {
            gameManager.setNumItem(4);
        }
        else if (ch == '5' && !gameManager.player.die) {
            gameManager.setNumItem(5);
        }

        if (gameManager.player.die) {
            gameManager.ui.drawDeathScreen();
        }
        else {
            gameManager.ui.updateGameScreen(); //Always update game screen
            gameManager.ui.updateUI(); //Always update UI
        }
    }

    //End ncurses
    endwin();
}