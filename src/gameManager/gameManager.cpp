#include "./gameManager.h"
#include <iostream>
#include <list>

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
}

void GameManager::restartGame() {
    dungeon.generateDungeon();
    player.clearPlayer();
    player.randomSpawnPlayer();
    door.randomPlaceDoor();
    coins.randomPlaceCoins();
}


