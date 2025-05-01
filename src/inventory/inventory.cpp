#include "./inventory.h"

void Inventory::addItemToInventory(Item item) {
    int* amount = inventoryTable.search(item);
    if (amount != nullptr) {
        (*amount)++;
    }
    else {
        inventoryKeys.push_back(item);
        inventoryTable.insert(item, 1);
    }
}

void Inventory::decreaseItemAmount(Item item) {
    int* amount = inventoryTable.search(item);
    if (amount != nullptr) {
        if (*amount - 1 > 0) {
            (*amount)--;
        }
        else {
            discardItemFromInventory(item);
        }
    }
}

void Inventory::discardItemFromInventory(Item item) {
    int* amount = inventoryTable.search(item);
    if (amount != nullptr) {
        inventoryTable.remove(item);
        auto it = std::find(inventoryKeys.begin(), inventoryKeys.end(), item);
        if (it != inventoryKeys.end()) {
            inventoryKeys.erase(it);
        }
    }
}

void Inventory::useItem(int index) {
    if (index < 0 || index >= inventoryKeys.size()) return;    
    Item item = inventoryKeys[index];
    item.use();
    decreaseItemAmount(item);
}

void Inventory::clearInventory() {
    inventoryTable.clearAll();
    inventoryKeys.clear();
}

vector<Item> Inventory::getInventoryKeys() {
    return inventoryKeys;
}

HashTable<Item, int> Inventory::getHashTable() {
    return inventoryTable;
}
