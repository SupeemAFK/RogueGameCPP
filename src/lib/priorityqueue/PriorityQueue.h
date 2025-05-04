#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <vector>
#include "../../dungeon/dungeon.h"

template <typename T>
class PriorityQueue {
public:
    void push(const T& item);
    void pop();
    T top() const;
    bool empty() const;
    size_t size() const;

private:
    std::vector<T> heap;

    void heapifyUp(size_t index);
    void heapifyDown(size_t index);
};

#endif // PRIORITY_QUEUE_H
