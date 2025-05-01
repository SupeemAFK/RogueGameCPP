#ifndef INVENTORY_H
#define INVENTORY_H

#include "../lib/hashtable/HashTable.h"
#include "../Item/item.h"

class Inventory {
    public:
        void addItemToInventory(Item itemName);
        void discardItemFromInventory(Item itemName);
        void clearInventory();
        HashTable<Item, int> getHashTable();

    private:
        HashTable<Item, int> inventoryTable;
};

#endif