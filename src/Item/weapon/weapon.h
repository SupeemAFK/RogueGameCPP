#ifndef WEAPON_H
#define WEAPON_H

#include "../item.h"

class Weapon : public Item {
    public:
        void use() override;
};

#endif