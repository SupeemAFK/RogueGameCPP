#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "../dungeon/dungeon.h"
#include "../coin/coin.h"
#include "../nextLevel/nextLevel.h"
#include "../player/player.h"
#include "../enemy/enemy.h"
#include <vector>

using namespace std;

class GameManager {
    public:
        vector<Enemy> enemies;        
        Dungeon& dungeon;
        Coin& coins;
        NextLevel& door;
        Player& player;
        GameManager(Dungeon& _dungeon, Coin& _coins, NextLevel& door, Player& _player);

        void startGame();
        void restartGame();
        void randomEnemiesPlacement();
};

#endif