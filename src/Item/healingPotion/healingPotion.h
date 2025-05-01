#ifndef HEALINGPOTION_H
#define HEALINGPOTION_H

#include "../item.h"

class HealingPotion : public Item {
    public:
        HealingPotion();
        void use() override;
};

#endif