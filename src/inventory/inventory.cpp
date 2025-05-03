#include "./inventory.h"
#include "../gameManager/gameManager.h"

Inventory::Inventory(GameManager* _gm) {
    gm = _gm;
}

bool Inventory::addItemToInventory(Item* item) {
    int* amount = inventoryTable.search(item->getName());
    if (amount != nullptr) {
        (*amount)++;
        return true;
    }
    else {
        if (isFull()) return false;
        inventoryKeys.push_back(item);
        inventoryTable.insert(item->getName(), 1);
        return true;
    }
}

void Inventory::decreaseItemAmount(Item* item) {
    int* amount = inventoryTable.search(item->getName());
    if (amount != nullptr) {
        if (*amount - 1 > 0) {
            (*amount)--;
        }
        else {
            discardItemFromInventory(item);
        }
    }
}

bool Inventory::discardItemFromInventory(Item* item) {
    int* amount = inventoryTable.search(item->getName());
    if (amount != nullptr) {
        gm->removeItem(item);
        inventoryTable.remove(item->getName());
        auto it = std::find(inventoryKeys.begin(), inventoryKeys.end(), item);
        if (it != inventoryKeys.end()) inventoryKeys.erase(it);
        return true;
    }
    else {
        return false;
    }
}

void Inventory::useItem(int index) {
    if (index < 0 || index >= inventoryKeys.size()) return;    
    Item* item = inventoryKeys[index];
    item->use();
    decreaseItemAmount(item);
}

bool Inventory::isFull() {
    return inventoryTable.isFull();
}

void Inventory::clearInventory() {
    inventoryTable.clearAll();
    inventoryKeys.clear();
}

vector<Item*> Inventory::getInventoryKeys() {
    return inventoryKeys;
}

HashTable<string, int> Inventory::getHashTable() {
    return inventoryTable;
}
