#include "PriorityQueue.h"
#include <stdexcept>

template <typename T, typename Compare>
void PriorityQueue<T, Compare>::heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (comp(heap[index], heap[parent])) {
            std::swap(heap[index], heap[parent]);
            index = parent;
        } else {
            break;
        }
    }
}

template <typename T, typename Compare>
void PriorityQueue<T, Compare>::heapifyDown(int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap.size() && comp(heap[left], heap[smallest])) {
        smallest = left;
    }
    if (right < heap.size() && comp(heap[right], heap[smallest])) {
        smallest = right;
    }

    if (smallest != index) {
        std::swap(heap[index], heap[smallest]);
        heapifyDown(smallest);
    }
}

template <typename T, typename Compare>
void PriorityQueue<T, Compare>::push(const T& value) {
    heap.push_back(value);
    heapifyUp(heap.size() - 1);
}

template <typename T, typename Compare>
void PriorityQueue<T, Compare>::pop() {
    if (heap.empty()) {
        throw std::runtime_error("Priority Queue is empty");
    }
    heap[0] = heap.back();
    heap.pop_back();
    if (!heap.empty()) {
        heapifyDown(0);
    }
}

template <typename T, typename Compare>
T PriorityQueue<T, Compare>::top() const {
    if (heap.empty()) {
        throw std::runtime_error("Priority Queue is empty");
    }
    return heap[0];
}

template <typename T, typename Compare>
bool PriorityQueue<T, Compare>::empty() const {
    return heap.empty();
}

template <typename T, typename Compare>
size_t PriorityQueue<T, Compare>::size() const {
    return heap.size();
}