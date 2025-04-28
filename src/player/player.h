#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "../dungeon/dungeon.h"
#include "../nextLevel/nextlevel.h"
#include "../coin/coin.h"

class Player {
    public:
        int playerX, playerY;
        int playerCoin;
        int playerFloor;
        char previousTile;
        Dungeon& dungeon;
        Coin& coin;
        NextLevel& door;
        
        Player(Dungeon& _dungeon, Coin& _coin, NextLevel& _door);

        void clearPlayer();
        void randomSpawnPlayer();
        void movePlayer(std::vector<int> direction);
};

#endif