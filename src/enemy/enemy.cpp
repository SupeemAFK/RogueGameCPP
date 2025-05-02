#include "./enemy.h"
#include "../player/player.h"
#include "../dungeon/dungeon.h"
#include "../gameManager/gameManager.h"
#include <random>

Enemy::Enemy(Player* _player, Dungeon* _dungeon, GameManager* _gm, float maxHealth, int _enemyX, int _enemyY) : 
    player(_player), 
    dungeon(_dungeon), 
    gm(_gm),
    health(maxHealth),
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
        //Attack player miss, chance etc..
        player->damaged(damage);
    }
}

void Enemy::damaged(float damage) {
    health -= damage;
    if (health <= 0) die();
}

void Enemy::die() {
    dungeon->map[monsterY][monsterX] = previousTile;
    gm->removeEnemy(this);
}