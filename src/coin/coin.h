#ifndef COIN_H
#define COIN_H

class Dungeon;

class Coin {
    public:
        Coin(Dungeon* _dungeon);
        void randomPlaceCoins();
    private:
        Dungeon* dungeon;
    
};

#endif