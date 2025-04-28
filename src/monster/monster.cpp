#include "./monster.h"

Enemy::Enemy(Player& _player, Dungeon& _dungeon, float maxHealth) : player(_player), dungeon(_dungeon), health(maxHealth) {}

void Enemy::randomSpawnMonster() {
    if (dungeon.rooms.empty()) return;

    int randomRoomIndex = rand() % dungeon.rooms.size();
    const Room& room = dungeon.rooms[randomRoomIndex];

    int monsterX = room.x + (std::rand() % room.width);
    int monsterY = room.y + (std::rand() % room.height);

    previousTile = dungeon.map[monsterX][monsterY];
    dungeon.map[monsterX][monsterY] = 'K';
}

void Enemy::randomMoveMonster(std::vector<int> direction) {
    int randomDirection = std::rand() % 2;

    int newPositionX;
    int newPositionY;

    //Move X
    if (randomDirection == 0) {
        int random = std::rand() % 2;
        int move = random == 1 ? 1 : -1;
        newPositionX - monsterX + move;
    }
    //Move Y
    else {
        int random = std::rand() % 2;
        int move = random == 1 ? 1 : -1;
        newPositionY = monsterY + move;
    }

    dungeon.map[monsterX][monsterY] = previousTile;
    monsterX = newPositionX;
    monsterY = newPositionY;
    previousTile = dungeon.map[monsterX][monsterY];
    dungeon.map[monsterX][monsterY] = 'K';
}

void Enemy::monveToPlayer() {
    int dx = player.playerX - monsterX;
    int dy = player.playerY - monsterY;

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

    dungeon.map[monsterX][monsterY] = previousTile;
    monsterX = newPositionX;
    monsterY = newPositionY;
    previousTile = dungeon.map[monsterX][monsterY];
    dungeon.map[monsterX][monsterY] = 'K';
}

void Enemy::attackPlayer() {
    if (dungeon.map[monsterX + 1] == "@" || 
        dungeon.map[monsterX - 1] == "@" || 
        dungeon.map[monsterY + 1] == "@" || 
        dungeon.map[monsterY - 1] == "@") 
    {
        //attack player
    }
}

void Enemy::damaged(float damage) {
    health -= damage;
}

void Enemy::die() {
    dungeon.map[monsterX][monsterY] = '.';
    delete this;
}