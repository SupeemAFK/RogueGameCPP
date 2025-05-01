#include "./gameManager.h"
#include <cstdlib>
#include <algorithm>

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
    enemies.clear();
    player.randomSpawnPlayer();
    door.randomPlaceDoor();
    coins.randomPlaceCoins();
    randomEnemiesPlacement();
    randomItemsPlacement();
}

void GameManager::restartGame() {
    dungeon.generateDungeon();
    enemies.clear();
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
        int isPlaced = rand() % 2;
        if (!isPlaced) continue; //Skip this room
        if (isPlaced) {
            int randomX = room.x + (rand() % room.width);
            int randomY = room.y + (rand() % room.height);
            if (dungeon.map[randomY][randomX] != '-' && dungeon.map[randomY][randomX] != '|') {
                if (dungeon.map[randomY][randomX] == '.') {
                    HealingPotion* healingPotion = new HealingPotion();
                    healingPotion->setX(randomX);
                    healingPotion->setY(randomY);
                    healingPotion->setGameManager(this);
                    dungeon.map[randomY][randomX] = healingPotion->getItemRender();
                    items.push_back(healingPotion);
                }
            }
        }
    }
}

void GameManager::removeItem(Item* item){
    auto it = find(items.begin(), items.end(), item);
    if (it != items.end()) {
        items.erase(it);
        delete item; //free memory
    }
}


