#ifndef INVENTORY_H
#define INVENTORY_H

#include "../lib/hashtable/HashTable.h"

class Inventory {
    public:
        HashTable<string, int> inventory;
        void addItemToInventory(string itemName);
        void discardItemFromInventory(string itemName);
};

#endif