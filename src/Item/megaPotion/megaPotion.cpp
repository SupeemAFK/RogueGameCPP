#include "./megaPotion.h"
#include "../../gameManager/gameManager.h"

MegaPotion::MegaPotion() 
    : Item("MegaPotion", "Restores FULL health when used.", 'm') //Like calling super()
{}

bool MegaPotion::use() {
    if (gm->player.getCurrentHealth() >= gm->player.maxHealth) return false;
    gm->player.healPlayer(100);
    return true;
}