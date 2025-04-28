#include "./coin.h"
#include <random>

using namespace std;

Coin::Coin(Dungeon& _dungeon) : dungeon(_dungeon) {}

void Coin::randomPlaceCoins() {
    if (dungeon.rooms.empty()) return;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, 1);

    for (const auto& room : dungeon.rooms) {
        int random_bit = distrib(gen);
        if (random_bit == 1) {
            int minX = room.x + 1; 
            int maxX = room.x + room.width - 2; 
            int minY = room.y + 1; 
            int maxY = room.y + room.height - 2;
            if (minX > maxX || minY > maxY) continue;

            uniform_int_distribution<> x_distrib(minX, maxX);
            uniform_int_distribution<> y_distrib(minY, maxY);

            int randomX = x_distrib(gen);
            int randomY = y_distrib(gen);

            if (dungeon.map[randomY][randomX] != '-' && dungeon.map[randomY][randomX] != '|') {
                if (dungeon.map[randomY][randomX] == '.') dungeon.map[randomY][randomX] = '$';
            }
        }
    }
}