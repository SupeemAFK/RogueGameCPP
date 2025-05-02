#include "./weapon.h"
#include "../../gameManager/gameManager.h"

Weapon::Weapon(string weaponName, string weaponDescriptions, char weaponRender, float _damage) : 
    Item(weaponName, weaponDescriptions, weaponRender),
    damage(_damage)
{}

void Weapon::use() {
    gm->player.setPlayerWeapon(this);
}