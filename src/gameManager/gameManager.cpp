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
}

void GameManager::goToNextFloor() {
    dungeon.generateDungeon();
    enemies.clear();
    player.randomSpawnPlayer();
    door.randomPlaceDoor();
    coins.randomPlaceCoins();
    randomEnemiesPlacement();
}

void GameManager::restartGame() {
    dungeon.generateDungeon();
    enemies.clear();
    player.clearPlayer();
    player.resetPlayer();
    player.randomSpawnPlayer();
    door.randomPlaceDoor();
    coins.randomPlaceCoins();
    randomEnemiesPlacement();
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
                    enemies.push_back(move(enemy));
                }
            }
        }
    }
}

void GameManager ::removeEnemy(Enemy* enemy) {
    auto it = find(enemies.begin(), enemies.end(), enemy);
    if (it != enemies.end()) {
        enemies.erase(it);
        delete enemy; //free memory
    }
}


