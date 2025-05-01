#include "./inventory.h"

void Inventory::addItemToInventory(Item item) {
    int* amount = inventoryTable.search(item);
    if (amount != nullptr) {
        (*amount)++;
    }
    else {
        inventoryTable.insert(item, 1);
    }
}

void Inventory::discardItemFromInventory(Item item) {
    int* amount = inventoryTable.search(item);
    if (amount != nullptr) {
        inventoryTable.remove(item);
    }
}

void Inventory::clearInventory() {
    inventoryTable.clearAll();
}

HashTable<Item, int> Inventory::getHashTable() {
    return inventoryTable;
}