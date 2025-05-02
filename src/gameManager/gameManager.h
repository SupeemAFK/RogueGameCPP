#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "../dungeon/dungeon.h"
#include "../coin/coin.h"
#include "../nextLevel/nextLevel.h"
#include "../player/player.h"
#include "../enemy/enemy.h"
#include "../inventory/inventory.h"
#include "../Item/item.h"
#include "../Item/healingPotion/healingPotion.h"
#include "../Item/megaPotion/megaPotion.h"
#include "../Item/weapon/SteelSword/steelSword.h"
#include "../Item/weapon/Dagger/dagger.h"
#include "../Item/weapon/Katana/katana.h"
#include <vector>

using namespace std;

class GameManager {
    public:
        vector<Enemy*> enemies;   
        vector<Item* > items;     
        Dungeon dungeon;
        Coin coins;
        NextLevel door;
        Player player;
        Inventory inventory;
        GameManager();

        void startGame();
        void goToNextFloor();
        void restartGame();
        void randomEnemiesPlacement();
        void removeEnemy(Enemy* enemy);
        void randomItemsPlacement();
        void removeItem(Item* item);

    private:
        bool placeItem(Item* item, const Room& room, float spawnChancePercent, bool multiplyFloor);
};

#endif