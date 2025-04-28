#ifndef MONSTER_H
#define MONSTER_H

#include "../player/player.h"
#include <vector>

class Enemy {
    public:
        int monsterX;
        int monsterY;

        Dungeon& dungeon;
        Player& player;
        Enemy(Player& _player, Dungeon& _dungeon, float maxHealth);
        
        void randomSpawnMonster();
        void randomMoveMonster(std::vector<int> direction);
        void monveToPlayer();
        void attackPlayer();
        void damaged(float damage);
        void die();

    private:
        char previousTile;
        float health;
};

#endif