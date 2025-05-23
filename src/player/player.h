#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <optional>
#include "../Item/weapon/weapon.h"

using namespace std;

class Dungeon;
class GameManager;

class Player {
    public:
        int playerX, playerY;
        int playerCoin;
        int playerFloor;
        int level;
        bool die = false;
        float EXP;
        float maxHealth;
        float baseAttack;
        
        Player(Dungeon* _dungeon, GameManager* _gm, float _maxHealth);

        void clearPlayer();
        void randomSpawnPlayer();
        void movePlayer(std::vector<int> direction);
        void damaged(float damage);
        void healPlayer(float amount);
        float getCurrentHealth();
        float getCurrentExp();
        void resetPlayer();
        optional<Weapon> getPlayerWeapon();
        void setPlayerWeapon(Weapon weapon);
        void removeWeapon();
        void increaseEXP(float exp);
        void levelUP();

    private:
        Dungeon* dungeon;
        GameManager* gm;
        optional<Weapon> playerWeapon;

        char previousTile;
        float health;
        float currentEXP;
};

#endif