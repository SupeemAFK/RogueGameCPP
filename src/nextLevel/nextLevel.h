#ifndef NEXTLEVEL_H
#define NEXTLEVEL_H

class Dungeon;

class NextLevel {
    public:
        NextLevel(Dungeon* _dungeon);
        
        void randomPlaceDoor();
    private:
        Dungeon* dungeon;
};

#endif