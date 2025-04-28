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
        float maxHealth;
        
        Dungeon& dungeon;
        Coin& coin;
        NextLevel& door;
        
        Player(Dungeon& _dungeon, Coin& _coin, NextLevel& _door, float _maxHealth);

        void clearPlayer();
        void randomSpawnPlayer();
        void movePlayer(std::vector<int> direction);
        void damaged(float damage);
        float getCurrentHealth();

    private:
        char previousTile;
        float health;
};

#endif