#include "./inventory.h"

void Inventory::addItemToInventory(string itemName) {
    int* amount = inventory.search(itemName);
    if (amount != nullptr) {
        (*amount)++;
    }
    else {
        inventory.insert(itemName, 1);
    }
}

void Inventory::discardItemFromInventory(string itemName) {
    int* amount = inventory.search(itemName);
    if (amount != nullptr) {
        inventory.remove(itemName);
    }
}