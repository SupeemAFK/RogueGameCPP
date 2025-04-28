#include "./nextLevel.h"

using namespace std;

NextLevel::NextLevel(Dungeon& _dungeon) : dungeon(_dungeon) {}

void NextLevel::randomPlaceDoor() {
    if (dungeon.rooms.empty()) return;

    const int maxAttempts = dungeon.rooms.size();
    for (int attempt = 0; attempt < maxAttempts; ++attempt) {
        int randomRoomIndex = rand() % dungeon.rooms.size();
        const Room& room = dungeon.rooms[randomRoomIndex];

        int X = room.centerY();
        int Y = room.centerX();

        if (dungeon.map[X][Y] != '@') {
            dungeon.map[X][Y] = 'D'; 
            return;
        }
    }
}