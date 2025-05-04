#include "./player.h"
#include "../dungeon/dungeon.h"
#include "../gameManager/gameManager.h"

Player::Player(Dungeon* _dungeon, GameManager* _gm, float _maxHealth) :
    playerX(0), 
    playerY(0), 
    level(1),
    playerCoin(0), 
    playerFloor(1), 
    playerWeapon(nullopt),
    previousTile('.'), 
    EXP(30),
    maxHealth(_maxHealth),
    health(_maxHealth),
    baseAttack(15),
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
    for (Enemy* enemy : gm->enemies) {
        if (enemy->monsterX == newPositionX && enemy->monsterY == newPositionY) {
            float roll = static_cast<float>(rand()) / RAND_MAX;
            if (playerWeapon == nullopt) {
                if (roll < 0.9) {
                    enemy->damaged(baseAttack);
                    gm->ui.addLog("Player attack 15 damage.");
                    return;
                } 
                else {
                    gm->ui.addLog("Player attack missed.");
                    return;
                }
            }
            else {
                if (roll < playerWeapon->hitChance) {
                    float netDamage = (baseAttack / 2) + playerWeapon->damage;
                    enemy->damaged(netDamage);

                    char buffer[256];
                    snprintf(buffer, sizeof(buffer), "Player attack %d damage", netDamage);
                    gm->ui.addLog(string(buffer));
                    return;
                } 
                else {
                    gm->ui.addLog("Player attack missed.");
                    return;
                }
            }
        }
    }
    //Check if item
    for (Item* item : gm->items) {
        if (item->getX() == newPositionX && item->getY() == newPositionY) {
            int* amount = gm->inventory.getHashTable().search(item->getName());
            if (amount == nullptr) {
                bool success = gm->inventory.addItemToInventory(item);
                if (success) dungeon->map[newPositionY][newPositionX] = '.';
                item->setX(-100000);
                item->setY(-100000);
            }
            else {
                bool success = gm->inventory.addItemToInventory(item);
                if (success) dungeon->map[newPositionY][newPositionX] = '.';
                gm->removeItem(item);
            }
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
    removeWeapon();
}

optional<Weapon> Player::getPlayerWeapon() {
    return playerWeapon;
}

void Player::setPlayerWeapon(Weapon weapon) {
    if (playerWeapon == nullopt) {
        playerWeapon = weapon;
    }
}

void Player::removeWeapon() {
    playerWeapon = nullopt;
}

void Player::increaseEXP(float exp) {
    if (currentEXP + exp >= EXP) levelUP();
    else currentEXP += exp;
}

void Player::levelUP() {
    level += 1;
    EXP = EXP * 1.35;
    baseAttack += 3.5;
    maxHealth += 10;
    currentEXP = 0;
}

float Player::getCurrentExp() {
    return currentEXP;
}