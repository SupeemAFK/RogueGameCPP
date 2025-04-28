#ifndef MONSTER_H
#define MONSTER_H

#include "../player/player.h"
#include "../dungeon/dungeon.h"

class Enemy {
    public:
        int monsterX;
        int monsterY;
        float damage = 10;
        char previousTile = '.';
        char monsterRender = 'K';
        
        Dungeon& dungeon;
        Player& player;
        Enemy(Player& _player, Dungeon& _dungeon, float maxHealth, int _enemyX, int _enemyY);
        
        void randomMoveMonster();
        void moveToPlayer();
        void damaged(float damage);
        void die();

    private:
        float health;
};

#endif