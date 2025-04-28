#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <string>

template <typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
    };

    Node* head;

public:
    LinkedList();
    ~LinkedList();

    void insert(const T& value);
    void remove(const T& value);
    void clearAll();
    void display() const;
};

#endif 
