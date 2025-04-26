#include <vector>
#include "../dungeon/dungeon.h"

using namespace std;

int playerX = 0, playerY = 0;
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

    map[playerY][playerX] = previousTile;
    playerX = newPositionX;
    playerY = newPositionY;
    previousTile = map[playerY][playerX];
    map[playerY][playerX] = '@';
}