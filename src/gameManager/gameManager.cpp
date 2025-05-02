#include "./gameManager.h"
#include <cstdlib>
#include <algorithm>
#include <time.h>

GameManager::GameManager() : 
    dungeon(),
    coins(&dungeon),
    door(&dungeon),
    player(&dungeon, this, 100),
    inventory()
{}

void GameManager::startGame() {
    dungeon.generateDungeon();
    player.randomSpawnPlayer();
    door.randomPlaceDoor();
    coins.randomPlaceCoins();
    randomEnemiesPlacement();
    randomItemsPlacement();
}

void GameManager::goToNextFloor() {
    dungeon.generateDungeon();

    for (auto enemy : enemies) {
        delete enemy;
    }
    enemies.clear();

    for (auto item : items) {
        delete item;
    }
    items.clear();

    player.randomSpawnPlayer();
    door.randomPlaceDoor();
    coins.randomPlaceCoins();
    randomEnemiesPlacement();
    randomItemsPlacement();
}

void GameManager::restartGame() {
    dungeon.generateDungeon();

    for (auto enemy : enemies) {
        delete enemy;
    }
    enemies.clear();

    for (auto item : items) {
        delete item;
    }
    items.clear();

    inventory.clearInventory();
    player.clearPlayer();
    player.resetPlayer();
    player.randomSpawnPlayer();
    door.randomPlaceDoor();
    coins.randomPlaceCoins();
    randomEnemiesPlacement();
    randomItemsPlacement();
}

void GameManager::randomEnemiesPlacement() {
    if (dungeon.rooms.empty()) return;

    for (const auto& room : dungeon.rooms) {
        int isPlaced = rand() % 2;
        if (!isPlaced) continue; //Skip this room
        if (isPlaced) {
            int randomX = room.x + (rand() % room.width);
            int randomY = room.y + (rand() % room.height);
            if (dungeon.map[randomY][randomX] != '-' && dungeon.map[randomY][randomX] != '|') {
                if (dungeon.map[randomY][randomX] == '.') {
                    Enemy* enemy = new Enemy(&player, &dungeon, this, 100, randomX, randomY);
                    enemy->previousTile = dungeon.map[randomY][randomX];
                    dungeon.map[randomY][randomX] = enemy->monsterRender;
                    enemies.push_back(enemy);
                }
            }
        }
    }
}

void GameManager::removeEnemy(Enemy* enemy) {
    auto it = find(enemies.begin(), enemies.end(), enemy);
    if (it != enemies.end()) {
        enemies.erase(it);
        delete enemy; //free memory
    }
}

void GameManager::randomItemsPlacement() {
    if (dungeon.rooms.empty()) return;

    for (const auto& room : dungeon.rooms) {
        //Potions
        HealingPotion* healingPotion = new HealingPotion();
        placeItem(healingPotion, room, 1, false);

        MegaPotion* megaPotion = new MegaPotion();
        placeItem(megaPotion, room, 0.25, false);

        //Weapons
        SteelSword* steelSword = new SteelSword();
        placeItem(steelSword, room, 0.0125, true);

        Dagger* dagger = new Dagger();
        placeItem(dagger, room, 0.025, true);

        Katana* katana = new Katana();
        placeItem(katana, room, 0.00625, true);

        Axe* axe = new Axe();
        placeItem(axe, room, 0.0125, true);

        Hammer* hammer = new Hammer();
        placeItem(hammer, room, 0.005, true);
    }
}

void GameManager::removeItem(Item* item){
    auto it = find(items.begin(), items.end(), item);
    if (it != items.end()) {
        items.erase(it);
        delete item; //free memory
    }
}

bool GameManager::placeItem(Item* item, const Room& room, float spawnChancePercent, bool multiplyFloor) {
    float multiplier = 1;
    if (multiplyFloor) {
        int tier = (player.playerFloor - 1) / 5;
        multiplier = 1.0 + 0.25 * tier;
    }

    float effectiveChance = spawnChancePercent * multiplier * 100.0f;
    if (effectiveChance > 100.0f) effectiveChance = 100.0f;

    float roll = static_cast<float>(rand()) / RAND_MAX * 100;
    if (roll >= effectiveChance) {
        delete item;
        return false;
    }

    const int maxAttempts = 10;
    for (int attempt = 0; attempt < maxAttempts; ++attempt) {
        int randomX = room.x + (rand() % room.width);
        int randomY = room.y + (rand() % room.height);
        char tile = dungeon.map[randomY][randomX];

        if (tile == '-' || tile == '|' || tile == '+' || tile == 'D' || tile == '@') continue;

        bool occupied = false;
        for (auto& existingItem : items) {
            if (existingItem->getX() == randomX && existingItem->getY() == randomY) {
                occupied = true;
                break;
            }
        }
        if (occupied) continue;

        item->setX(randomX);
        item->setY(randomY);
        item->setGameManager(this);
        dungeon.map[randomY][randomX] = item->getItemRender();
        items.push_back(item);
        return true;
    }

    //return false when fail to find postion after many tries
    delete item;
    return false;
}