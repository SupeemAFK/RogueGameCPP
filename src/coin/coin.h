#ifndef COIN_H
#define COIN_H

#include "../dungeon/dungeon.h"

class Coin {
    public:
        Dungeon& dungeon;
        Coin(Dungeon& _dungeon);
        void randomPlaceCoins();
};

#endif