#include "./weapon.h"
#include "../../gameManager/gameManager.h"

Weapon::Weapon(string weaponName, string weaponDescriptions, char weaponRender, float _damage, float _hitChance) : 
    Item(weaponName, weaponDescriptions, weaponRender),
    damage(_damage),
    hitChance(_hitChance)
{}

void Weapon::use() {
    gm->player.setPlayerWeapon(*this);
}