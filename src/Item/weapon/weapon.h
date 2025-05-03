#ifndef WEAPON_H
#define WEAPON_H

#include "../item.h"
#include <string>

using namespace std;

class Weapon : public Item {
    public:
        Weapon(string weaponName, string weaponDescriptions, char weaponRender, float _damage, float _hitChance);
        float damage;
        float hitChance;
        void use() override;
};

#endif