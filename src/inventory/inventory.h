#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include <vector>
#include <functional>
#include "../lib/hashtable/HashTable.h"
#include "../Item/item.h"

using namespace std;

class GameManager;

class Inventory {
    public:
        Inventory(GameManager* _gm);

        bool addItemToInventory(Item* itemName);
        void decreaseItemAmount(Item* itemName);
        bool discardItemFromInventory(Item* itemName);
        void useItem(int index);
        void clearInventory();
        bool isFull();
        vector<Item*> getInventoryKeys();
        HashTable<string, int> getHashTable();

    private:
        GameManager* gm;

        HashTable<string, int> inventoryTable;
        vector<Item*> inventoryKeys;
};

#endif