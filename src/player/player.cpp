#include <vector>
#include "./player.h"

using namespace std;

Player::Player(Dungeon& _dungeon, Coin& _coin, NextLevel& _door) :
    playerX(0), 
    playerY(0), 
    playerCoin(0), 
    playerFloor(1), 
    previousTile('.'), 
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

    if (dungeon.map[newPositionY][newPositionX] == '|' || dungeon.map[newPositionY][newPositionX] == '-' || dungeon.map[newPositionY][newPositionX] == ' ') {
        return;
    }
    else if (dungeon.map[newPositionY][newPositionX] == '$') {
        playerCoin++;
        dungeon.map[newPositionY][newPositionX] = '.';
    }
    else if (dungeon.map[newPositionY][newPositionX] == 'D') {
        dungeon.generateDungeon();
        clearPlayer();
        randomSpawnPlayer();
        door.randomPlaceDoor();
        coin.randomPlaceCoins();
        playerFloor++;
        return;
    }

    dungeon.map[playerY][playerX] = previousTile;
    playerX = newPositionX;
    playerY = newPositionY;
    previousTile = dungeon.map[playerY][playerX];
    dungeon.map[playerY][playerX] = '@';
}