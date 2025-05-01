#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include <vector>
#include "../lib/hashtable/HashTable.h"
#include "../Item/item.h"

using namespace std;

class Inventory {
    public:
        void addItemToInventory(Item itemName);
        void decreaseItemAmount(Item itemName);
        void discardItemFromInventory(Item itemName);
        void useItem(int index);
        void clearInventory();
        vector<Item> getInventoryKeys();
        HashTable<Item, int> getHashTable();

    private:
        HashTable<Item, int> inventoryTable;
        vector<Item> inventoryKeys;
};

#endif