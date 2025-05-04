#ifndef HEALINGPOTION_H
#define HEALINGPOTION_H

#include "../item.h"

class HealingPotion : public Item {
    public:
        HealingPotion();
        bool use() override;
};

#endif