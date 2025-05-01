#include "./healingPotion.h"
#include "../../gameManager/gameManager.h"

HealingPotion::HealingPotion() 
    : Item("HealingPotion", "Restores health when used.", 'o') //Like calling super()
{}

void HealingPotion::use() {
    gm->restartGame();
}