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
        vector<Enemy*> enemies;        
        Dungeon dungeon;
        Coin coins;
        NextLevel door;
        Player player;
        GameManager();

        void startGame();
        void goToNextFloor();
        void restartGame();
        void randomEnemiesPlacement();
        void removeEnemy(Enemy* enemy);
};

#endif