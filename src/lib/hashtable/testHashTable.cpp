#include "HashTable.h"
#include <iostream>

template <typename KeyType, typename ValueType>
HashTable<KeyType, ValueType>::HashTable() {}

template <typename KeyType, typename ValueType>
int HashTable<KeyType, ValueType>::hashFunction(const KeyType& key) const {
    int hash = 0;
    string keyStr = to_string(key);
    for (char c : keyStr) {
        hash = (hash * 31 + c) % tableSize;
    }
    return hash;
}

template <typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::insert(const KeyType& key, const ValueType& value) {
    int index = hashFunction(key);
    int startIndex = index;

    while (table[index].occupied && table[index].key != key) {
        index = (index + 1) % tableSize;
        if (index == startIndex) {
            return;
        }
    }

    table[index].key = key;
    table[index].value = value;
    table[index].occupied = true;
}

template <typename KeyType, typename ValueType>
ValueType* HashTable<KeyType, ValueType>::search(const KeyType& key) {
    int index = hashFunction(key);
    int startIndex = index;

    while (table[index].occupied) {
        if (table[index].key == key) {
            return &(table[index].value);
        }
        index = (index + 1) % tableSize;
        if (index == startIndex) {
            break;
        }
    }
    return nullptr;
}

template <typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::remove(const KeyType& key) {
    int index = hashFunction(key);
    int startIndex = index;

    while (table[index].occupied) {
        if (table[index].key == key) {
            table[index].occupied = false;
            return;
        }
        index = (index + 1) % tableSize;
        if (index == startIndex) {
            break;
        }
    }
}

template <typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::clearAll() {
    for (int i = 0; i < tableSize; ++i) {
        table[i].occupied = false;
    }
}

int main() {
    HashTable<int, string> hashTable;

    while (true) {
        cout << "\nSelect Operations:\n";
        cout << "1. Insert\n";
        cout << "2. Search\n";
        cout << "3. Remove\n";
        cout << "4. Clear All\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        
        int choice;
        cin >> choice;

        if (choice == 1) {
            int key;
            string value;
            cout << "Enter key: ";
            cin >> key;
            cout << "Enter value: ";
            cin >> value;
            hashTable.insert(key, value);
            cout << "Inserted key " << key << " with value: " << value << endl;
        } 
        else if (choice == 2) {
            int key;
            cout << "Enter key to search: ";
            cin >> key;
            string* value = hashTable.search(key);
            if (value) {
                cout << "Found value for key " << key << ": " << *value << endl;
            } else {
                cout << "Key " << key << " not found." << endl;
            }
        } 
        else if (choice == 3) {
            int key;
            cout << "Enter key to remove: ";
            cin >> key;
            hashTable.remove(key);
            cout << "Removed key " << key << " from the table." << endl;
        } 
        else if (choice == 4) {
            hashTable.clearAll();
            cout << "All entries cleared from the hash table." << endl;
        } 
        else if (choice == 5) {
            cout << "Exiting program." << endl;
            break;
        } 
        else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}