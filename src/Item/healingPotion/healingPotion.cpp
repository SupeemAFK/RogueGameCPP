#include "./healingPotion.h"
#include "../../gameManager/gameManager.h"

HealingPotion::HealingPotion() 
    : Item("HealingPotion", "Restores 15 health when used.", 'o') //Like calling super()
{}

bool HealingPotion::use() {
    if (gm->player.getCurrentHealth() >= gm->player.maxHealth) return false;
    gm->player.healPlayer(15);
    return true;
}