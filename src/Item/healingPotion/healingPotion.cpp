#include "./healingPotion.h"
#include "../../gameManager/gameManager.h"

HealingPotion::HealingPotion() 
    : Item("HealingPotion", "Restores 15 health when used.", 'o') //Like calling super()
{}

void HealingPotion::use() {
    gm->player.healPlayer(15);
}