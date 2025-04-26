#include "../dungeon/dungeon.h"

using namespace std;

void randomPlaceDoor() {
    if (rooms.empty()) return;

    const int maxAttempts = rooms.size();
    for (int attempt = 0; attempt < maxAttempts; ++attempt) {
        int randomRoomIndex = rand() % rooms.size();
        const Room& room = rooms[randomRoomIndex];

        int X = room.centerY();
        int Y = room.centerX();

        if (map[X][Y] != '@') {
            map[X][Y] = 'D'; 
            return;
        }
    }
}