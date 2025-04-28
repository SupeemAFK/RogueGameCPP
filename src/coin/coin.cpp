#include "./coin.h"
#include <cstdlib>

using namespace std;

Coin::Coin(Dungeon& _dungeon) : dungeon(_dungeon) {}

void Coin::randomPlaceCoins() {
    if (dungeon.rooms.empty()) return;

    for (const auto& room : dungeon.rooms) {
        int isPlaced = rand() % 2;
        if (isPlaced) {
            int randomX = room.x + (rand() % room.width);
            int randomY = room.y + (rand() % room.height);
            if (dungeon.map[randomY][randomX] != '-' && dungeon.map[randomY][randomX] != '|') {
                if (dungeon.map[randomY][randomX] == '.') dungeon.map[randomY][randomX] = '$';
            }
        }
    }
}