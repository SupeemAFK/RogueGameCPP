#include "./enemy.h"
#include "../player/player.h"
#include "../dungeon/dungeon.h"
#include "../gameManager/gameManager.h"
#include <random>

Enemy::Enemy(Player* _player, Dungeon* _dungeon, GameManager* _gm, float _maxHealth, float _damage, int _enemyX, int _enemyY) : 
    player(_player), 
    dungeon(_dungeon), 
    gm(_gm),
    maxHealth(_maxHealth),
    health(_maxHealth),
    damage(_damage),
    monsterX(_enemyX),
    monsterY(_enemyY)
{}

void Enemy::randomMoveMonster() {
    int randomDirection = std::rand() % 2;
    int newPositionX = monsterX;
    int newPositionY = monsterY;

    int random = std::rand() % 2;
    int move = random == 1 ? 1 : -1;
    //Move X
    if (randomDirection == 0) {
        newPositionX = monsterX + move;
    } 
    //Move Y
    else {
        newPositionY = monsterY + move;
    }

    //Check overbound
    if (newPositionY < 0 || newPositionY >= dungeon->map.size() ||
        newPositionX < 0 || newPositionX >= dungeon->map[0].size()) {
        return; 
    }

    //Check instances
    char nextTile = dungeon->map[newPositionY][newPositionX];
    if (nextTile == '|' || 
        nextTile == '-' || 
        nextTile == ' ' || 
        nextTile == '#' || 
        nextTile == '+' || 
        nextTile == '@' ||
        nextTile == 'K'
    ) {
        return; 
    }

    dungeon->map[monsterY][monsterX] = previousTile; 
    monsterX = newPositionX;
    monsterY = newPositionY;
    previousTile = dungeon->map[monsterY][monsterX];
    dungeon->map[monsterY][monsterX] = monsterRender; 
}

void Enemy::moveToPlayer() {
    int dx = player->playerX - monsterX;
    int dy = player->playerY - monsterY;

    int newPositionX;
    int newPositionY;

    if (abs(dx) > abs(dy)) {
        if (dx > 0) newPositionX = monsterX + 1;
        else if (dx < 0) newPositionX = monsterX - 1;
    } 
    else {
        if (dy > 0) newPositionY = monsterY + 1; 
        else if (dy < 0) newPositionY = monsterY - 1;
    }

    dungeon->map[monsterY][monsterX] = previousTile; 
    monsterX = newPositionX;
    monsterY = newPositionY;
    previousTile = dungeon->map[monsterY][monsterX];
    dungeon->map[monsterY][monsterX] = monsterRender; 
}

void Enemy::checkNextToPlayer() {
    if ((monsterY > 0 && dungeon->map[monsterY - 1][monsterX] == '@') || // up
    (monsterY + 1 < dungeon->map.size() && dungeon->map[monsterY + 1][monsterX] == '@') || // down
    (monsterX > 0 && dungeon->map[monsterY][monsterX - 1] == '@') || // left
    (monsterX + 1 < dungeon->map[0].size() && dungeon->map[monsterY][monsterX + 1] == '@')) // right
    {
        float roll = static_cast<float>(rand()) / RAND_MAX;
        if (roll < hitChance) {
            player->damaged(damage);

            char buffer[256];
            snprintf(buffer, sizeof(buffer), "Enemy attack %.2f damage", damage);
            gm->ui.addLog(string(buffer));
        }
        else {
            gm->ui.addLog("Enemy attack missed.");
        }
    }
}

void Enemy::damaged(float damage) {
    health -= damage;
    if (health <= 0) die();
}

void Enemy::die() {
    gm->player.increaseEXP(8);
    dungeon->map[monsterY][monsterX] = previousTile;
    gm->removeEnemy(this);
}