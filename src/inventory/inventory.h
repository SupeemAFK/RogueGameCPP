#ifndef INVENTORY_H
#define INVENTORY_H

#include "../lib/hashtable/HashTable.h"

class Inventory {
    public:
        void addItemToInventory(string itemName);
        void discardItemFromInventory(string itemName);

    private:
        HashTable<string, int> inventory;
};

#endif