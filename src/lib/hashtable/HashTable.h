#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>

using namespace std;

template <typename KeyType, typename ValueType>
class HashTable {
private:
    struct Entry {
        KeyType key;
        ValueType value;
        bool occupied = false;
    };

    static const int tableSize = 5;
    Entry table[tableSize];

    int hashFunction(const KeyType& key) const;

public:
    HashTable();

    void insert(const KeyType& key, const ValueType& value);
    ValueType* search(const KeyType& key);
    void remove(const KeyType& key);
    void clearAll();
};

#endif // HASHTABLE_H
