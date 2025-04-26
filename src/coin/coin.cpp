#include "../dungeon/dungeon.h"
#include <random>

using namespace std;

void randomPlaceCoins() {
    if (rooms.empty()) return;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, 1);

    for (const auto& room : rooms) {
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

            if (map[randomY][randomX] != '-' && map[randomY][randomX] != '|') {
                if (map[randomY][randomX] == '.') map[randomY][randomX] = '$';
            }
        }
    }
}