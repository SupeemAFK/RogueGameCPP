#include "./megaPotion.h"
#include "../../gameManager/gameManager.h"

MegaPotion::MegaPotion() 
    : Item("MegaPotion", "Restores FULL health when used.", 'm') //Like calling super()
{}

void MegaPotion::use() {
    gm->player.healPlayer(100);
}