#ifndef MEGA_H
#define MEGA_H

#include "../item.h"

class MegaPotion : public Item {
    public:
        MegaPotion();
        void use() override;
};

#endif