#include <vector>
#include "../dungeon/dungeon.h"
#include "../nextLevel/nextlevel.h"
#include "../coin/coin.h"

using namespace std;

int playerX = 0, playerY = 0;
int playerCoin = 0;
int playerFloor = 1;
char previousTile;

void clearPlayer() {
    map[playerY][playerX] = '.';
}

void randomSpawnPlayer() {
    if (rooms.empty()) return;

    int randomRoomIndex = rand() % rooms.size();
    const Room& room = rooms[randomRoomIndex];

    playerY = room.centerY();
    playerX = room.centerX();

    previousTile = map[playerY][playerX];
    map[playerY][playerX] = '@';
}

void movePlayer(vector<int> direction) {
    int newPositionX = playerX + direction[0];
    int newPositionY = playerY + direction[1];

    if (map[newPositionY][newPositionX] == '|' || map[newPositionY][newPositionX] == '-' || map[newPositionY][newPositionX] == ' ') {
        return;
    }
    else if (map[newPositionY][newPositionX] == '$') {
        playerCoin++;
        map[newPositionY][newPositionX] = '.';
    }
    else if (map[newPositionY][newPositionX] == 'D') {
        generateDungeon();
        clearPlayer();
        randomSpawnPlayer();
        randomPlaceDoor();
        randomPlaceCoins();
        playerFloor++;
        return;
    }

    map[playerY][playerX] = previousTile;
    playerX = newPositionX;
    playerY = newPositionY;
    previousTile = map[playerY][playerX];
    map[playerY][playerX] = '@';
}