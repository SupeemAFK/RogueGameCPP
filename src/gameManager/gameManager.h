#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "../UI/ui.h"
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
#include "../Item/weapon/Axe/axe.h"
#include "../Item/weapon/Hammer/hammer.h"
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
        GameUI ui;
        GameManager();

        void startGame();
        void goToNextFloor();
        void restartGame();
        void randomEnemiesPlacement();
        void removeEnemy(Enemy* enemy);
        void randomItemsPlacement();
        void removeItem(Item* item);
        int getNumItem();
        void setNumItem(int num);

    private:
        int numItem = 1;

        bool placeItem(Item* item, const Room& room, float spawnChancePercent, bool multiplyFloor);
};

#endif