#include <vector>
#include "./player.h"

using namespace std;

Player::Player(Dungeon& _dungeon, Coin& _coin, NextLevel& _door, float _maxHealth) :
    playerX(0), 
    playerY(0), 
    level(1),
    playerCoin(0), 
    playerFloor(1), 
    previousTile('.'), 
    maxHealth(_maxHealth),
    health(_maxHealth),
    dungeon(_dungeon), 
    coin(_coin), 
    door(_door)
{}

void Player::clearPlayer() {
    dungeon.map[playerY][playerX] = '.';
}

void Player::randomSpawnPlayer() {
    if (dungeon.rooms.empty()) return;

    int randomRoomIndex = rand() % dungeon.rooms.size();
    const Room& room = dungeon.rooms[randomRoomIndex];

    playerY = room.centerY();
    playerX = room.centerX();

    previousTile = dungeon.map[playerY][playerX];
    dungeon.map[playerY][playerX] = '@';
}

void::Player::movePlayer(vector<int> direction) {
    int newPositionX = playerX + direction[0];
    int newPositionY = playerY + direction[1];

    //Check if walls
    if (dungeon.map[newPositionY][newPositionX] == '|' || dungeon.map[newPositionY][newPositionX] == '-' || dungeon.map[newPositionY][newPositionX] == ' ') {
        return;
    }
    //Check if coin
    else if (dungeon.map[newPositionY][newPositionX] == '$') {
        playerCoin++;
        dungeon.map[newPositionY][newPositionX] = '.';
    }
    //Check if door
    else if (dungeon.map[newPositionY][newPositionX] == 'D') {
        dungeon.generateDungeon();
        clearPlayer();
        randomSpawnPlayer();
        door.randomPlaceDoor();
        coin.randomPlaceCoins();
        playerFloor++;
        return;
    }
    //Check if enemy
    else if (dungeon.map[newPositionY][newPositionX] == 'K') {
        //Attack enemy miss, chance etc..
        return;
    }

    dungeon.map[playerY][playerX] = previousTile;
    playerX = newPositionX;
    playerY = newPositionY;
    previousTile = dungeon.map[playerY][playerX];
    dungeon.map[playerY][playerX] = '@';
}

void Player::damaged(float damage) {
    health -= damage;
    if (health <= 0) die = true;
}

float Player::getCurrentHealth() {
    return health;
}

void Player::resetPlayer() {
    health = maxHealth;
    playerCoin = 0;
    playerFloor = 1;
    level = 1;
}
