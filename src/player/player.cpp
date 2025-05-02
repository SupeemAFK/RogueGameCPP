#include <vector>
#include "./player.h"
#include "../dungeon/dungeon.h"
#include "../gameManager/gameManager.h"

using namespace std;

Player::Player(Dungeon* _dungeon, GameManager* _gm, float _maxHealth) :
    playerX(0), 
    playerY(0), 
    level(1),
    playerCoin(0), 
    playerFloor(1), 
    playerWeapon(nullptr),
    previousTile('.'), 
    maxHealth(_maxHealth),
    health(_maxHealth),
    dungeon(_dungeon), 
    gm(_gm)
{}

void Player::clearPlayer() {
    dungeon->map[playerY][playerX] = '.';
}

void Player::randomSpawnPlayer() {
    if (dungeon->rooms.empty()) return;

    int randomRoomIndex = rand() % dungeon->rooms.size();
    const Room& room = dungeon->rooms[randomRoomIndex];

    playerY = room.centerY();
    playerX = room.centerX();

    previousTile = dungeon->map[playerY][playerX];
    dungeon->map[playerY][playerX] = '@';
}

void::Player::movePlayer(vector<int> direction) {
    int newPositionX = playerX + direction[0];
    int newPositionY = playerY + direction[1];

    //Check if walls
    if (dungeon->map[newPositionY][newPositionX] == '|' || dungeon->map[newPositionY][newPositionX] == '-' || dungeon->map[newPositionY][newPositionX] == ' ') {
        return;
    }
    //Check if coin
    else if (dungeon->map[newPositionY][newPositionX] == '$') {
        playerCoin++;
        dungeon->map[newPositionY][newPositionX] = '.';
    }
    //Check if door
    else if (dungeon->map[newPositionY][newPositionX] == 'D') {
        gm->goToNextFloor();
        playerFloor++;
        return;
    }
    //Check if enemy
    for (auto& enemy : gm->enemies) {
        if (enemy->monsterX == newPositionX && enemy->monsterY == newPositionY) {
            //Attack enemy miss, chance etc..
            enemy->damaged(50);
            return;
        }
    }
    //Check if item
    for (auto& item : gm->items) {
        if (item->getX() == newPositionX && item->getY() == newPositionY) {
            bool success = gm->inventory.addItemToInventory(item);
            if (success) dungeon->map[newPositionY][newPositionX] = '.';
        }
    }


    dungeon->map[playerY][playerX] = previousTile;
    playerX = newPositionX;
    playerY = newPositionY;
    previousTile = dungeon->map[playerY][playerX];
    dungeon->map[playerY][playerX] = '@';
}

void Player::damaged(float damage) {
    health -= damage;
    if (health <= 0) die = true;
}

void Player::healPlayer(float amount) {
    if (health + amount >= maxHealth) {
        health = maxHealth;
    }
    else {
        health += amount;
    }
}

float Player::getCurrentHealth() {
    return health;
}

void Player::resetPlayer() {
    health = maxHealth;
    playerCoin = 0;
    playerFloor = 1;
    level = 1;
}

Weapon* Player::getPlayerWeapon() {
    return playerWeapon;
}

void Player::setPlayerWeapon(Weapon* weapon) {
    if (playerWeapon == nullptr) {
        playerWeapon = weapon;
    }
}