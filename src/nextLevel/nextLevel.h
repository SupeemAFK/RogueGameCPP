#ifndef NEXTLEVEL_H
#define NEXTLEVEL_H

#include "../dungeon/dungeon.h"

class NextLevel {
    public:
        Dungeon& dungeon;
        NextLevel(Dungeon& _dungeon);
        
        void randomPlaceDoor();
};

#endif