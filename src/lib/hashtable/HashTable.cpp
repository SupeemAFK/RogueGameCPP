#include "HashTable.h"
#include <iostream>

template <typename KeyType, typename ValueType>
HashTable<KeyType, ValueType>::HashTable() {}

template <typename KeyType, typename ValueType>
int HashTable<KeyType, ValueType>::hashFunction(const KeyType& key) const {
    string keyStr;

    if constexpr (is_same<KeyType, string>::value) {
        keyStr = key;
    } else {
        keyStr = to_string(key);
    }

    int hash = 0;
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

template class HashTable<string, int>;