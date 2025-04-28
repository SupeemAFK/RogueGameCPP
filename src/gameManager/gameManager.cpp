#include "./gameManager.h"
#include <cstdlib>

GameManager::GameManager(Dungeon& _dungeon, Coin& _coin, NextLevel& _door, Player& _player) : 
    dungeon(_dungeon),
    coins(_coin),
    door(_door),
    player(_player)
{}

void GameManager::startGame() {
    dungeon.generateDungeon();
    player.randomSpawnPlayer();
    door.randomPlaceDoor();
    coins.randomPlaceCoins();
    randomEnemiesPlacement();
}

void GameManager::restartGame() {
    dungeon.generateDungeon();
    player.clearPlayer();
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
                    Enemy enemy(player, dungeon, 100, randomX, randomY);
                    enemy.previousTile = dungeon.map[randomY][randomX];
                    dungeon.map[randomY][randomX] = enemy.monsterRender;
                    enemies.push_back(move(enemy));
                }
            }
        }
    }
}


