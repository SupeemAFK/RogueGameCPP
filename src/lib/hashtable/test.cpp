#include "HashTable.h"
#include <iostream>
#include <string>
#include <cassert>

using namespace std;

void report(bool condition, const string& message) {
    if (condition) {
        cout << "[PASS] " << message << "\n";
    } else {
        cout << "[FAIL] " << message << "\n";
    }
}

void testInsertAndSearch() {
    cout << "\n--- Test Case 1: Insert and Search ---\n";
    HashTable<string, int> ht;

    ht.insert("apple", 1);
    ht.insert("banana", 2);
    ht.insert("cherry", 3);

    report(ht.search("apple") && *ht.search("apple") == 1, "Search apple = 1");
    report(ht.search("banana") && *ht.search("banana") == 2, "Search banana = 2");
    report(ht.search("cherry") && *ht.search("cherry") == 3, "Search cherry = 3");
    report(ht.search("durian") == nullptr, "Search durian = nullptr");
}

void testUpdateValue() {
    cout << "\n--- Test Case 2: Update Existing Value ---\n";
    HashTable<string, int> ht;

    ht.insert("apple", 1);
    ht.insert("apple", 42); // update

    report(ht.search("apple") && *ht.search("apple") == 42, "Updated apple to 42");
}

void testRemove() {
    cout << "\n--- Test Case 3: Remove Key ---\n";
    HashTable<string, int> ht;

    ht.insert("apple", 1);
    ht.insert("banana", 2);
    ht.remove("apple");

    report(ht.search("apple") == nullptr, "Removed apple");
    report(ht.search("banana") && *ht.search("banana") == 2, "banana remains");
}

void testRehashClusterAfterDelete() {
    cout << "\n--- Test Case 4: Rehashing After Delete ---\n";
    HashTable<string, int> ht;

    ht.insert("key1", 1);
    ht.insert("key2", 2); // assume collision
    ht.remove("key1");

    report(ht.search("key2") && *ht.search("key2") == 2, "key2 still found after key1 deleted");
}

void testIsFullAndClearAll() {
    cout << "\n--- Test Case 5: isFull and clearAll ---\n";
    HashTable<string, int> ht;

    for (int i = 0; i < 10; ++i) {
        ht.insert("key" + to_string(i), i);
    }

    report(ht.isFull(), "HashTable is full after 10 inserts");

    ht.clearAll();

    report(!ht.isFull(), "HashTable is not full after clearAll");

    bool allCleared = true;
    for (int i = 0; i < 10; ++i) {
        if (ht.search("key" + to_string(i)) != nullptr) {
            report(false, "key" + to_string(i) + " still found after clearAll");
            allCleared = false;
        }
    }
    if (allCleared) report(true, "All keys cleared successfully");
}

int main() {
    testInsertAndSearch();
    testUpdateValue();
    testRemove();
    testRehashClusterAfterDelete();
    testIsFullAndClearAll();

    cout << "\n=== All HashTable Tests Finished ===\n";
}
