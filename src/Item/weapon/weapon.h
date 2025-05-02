#ifndef WEAPON_H
#define WEAPON_H

#include "../item.h"
#include <string>

using namespace std;

class Weapon : public Item {
    public:
        Weapon(string weaponName, string weaponDescriptions, char weaponRender, float _damage);
        float damage;
        void use() override;
};

#endif