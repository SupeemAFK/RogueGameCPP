#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

class Dungeon;
class GameManager;

class Player {
    public:
        int playerX, playerY;
        int playerCoin;
        int playerFloor;
        int level;
        bool die = false;
        float maxHealth;
        
        Player(Dungeon* _dungeon, GameManager* _gm, float _maxHealth);

        void clearPlayer();
        void randomSpawnPlayer();
        void movePlayer(std::vector<int> direction);
        void damaged(float damage);
        float getCurrentHealth();
        void resetPlayer();

    private:
        Dungeon* dungeon;
        GameManager* gm;

        char previousTile;
        float health;
};

#endif