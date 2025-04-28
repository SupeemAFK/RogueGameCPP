#include "./dungeon/dungeon.h"
#include "./UI/ui.h"
#include "./player/player.h"
#include "./coin/coin.h"
#include "./nextLevel/nextLevel.h"
#include <ctime>
#include <iostream>

int main() {
    srand(time(0));

    //Start
    Dungeon dungeon;
    Coin coin(dungeon);
    NextLevel nextLevelDoor(dungeon);
    Player player(dungeon, coin, nextLevelDoor);
    GameUI ui(dungeon, player);

    dungeon.generateDungeon();
    player.randomSpawnPlayer();
    nextLevelDoor.randomPlaceDoor();
    coin.randomPlaceCoins();
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
            dungeon.generateDungeon();
            player.clearPlayer();
            player.randomSpawnPlayer();
            nextLevelDoor.randomPlaceDoor();
            coin.randomPlaceCoins();
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

        //Always update game screen
        ui.updateGameScreen();
    }

    //End ncurses
    endwin();
}