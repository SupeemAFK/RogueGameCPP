#ifndef MONSTER_H
#define MONSTER_H

class Player;
class Dungeon;
class GameManager;

class Enemy {
    public:
        int monsterX;
        int monsterY;
        float damage = 10;
        float hitChance = 0.35;
        char previousTile = '.';
        char monsterRender = 'K';
        
        Enemy(Player* _player, Dungeon* _dungeon, GameManager* _gm, float maxHealth, int _enemyX, int _enemyY);
        
        void randomMoveMonster();
        void moveToPlayer();
        void checkNextToPlayer();
        void damaged(float damage);
        void die();

    private:
        GameManager* gm;
        Dungeon* dungeon;
        Player* player;
        float health;
};

#endif