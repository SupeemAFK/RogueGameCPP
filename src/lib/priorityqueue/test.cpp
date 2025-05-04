#include <iostream>
#include "PriorityQueue.h"
#include <cassert>
#include <stdexcept>

void report(bool condition, const std::string& message) {
    if (condition) {
        std::cout << "[PASS] " << message << "\n";
    } else {
        std::cout << "[FAIL] " << message << "\n";
    }
}

void test_basic_push_pop() {
    PriorityQueue<int> pq;
    std::cout << "\n--- Test Case 1: Basic Push/Pop ---\n";
    pq.push(10);
    pq.push(5);
    pq.push(20);
    pq.push(1);

    report(pq.top() == 1, "Top should be 1");
    pq.pop();
    report(pq.top() == 5, "Top after popping 1 should be 5");
    pq.pop();
    report(pq.top() == 10, "Top after popping 5 should be 10");

    report(!pq.empty(), "Queue should not be empty");
    report(pq.size() == 2, "Size should be 2");

    pq.pop();
    pq.pop();
    report(pq.empty(), "Queue should be empty after popping all");
    report(pq.size() == 0, "Size should be 0");

    try {
        pq.top();
        report(false, "Calling top() on empty queue should throw");
    } catch (const std::out_of_range&) {
        report(true, "Caught std::out_of_range from top() as expected");
    }

    try {
        pq.pop();
        report(false, "Calling pop() on empty queue should throw");
    } catch (const std::out_of_range&) {
        report(true, "Caught std::out_of_range from pop() as expected");
    }
}

void test_sorted_insert() {
    PriorityQueue<int> pq;
    std::cout << "\n--- Test Case 2: Insert in Sorted Order ---\n";
    pq.push(1);
    pq.push(2);
    pq.push(3);
    pq.push(4);
    report(pq.top() == 1, "Top should be 1");
    pq.pop();
    report(pq.top() == 2, "Top after popping 1 should be 2");
}

void test_reverse_insert() {
    PriorityQueue<int> pq;
    std::cout << "\n--- Test Case 3: Insert in Reverse Order ---\n";
    pq.push(100);
    pq.push(50);
    pq.push(10);
    pq.push(5);
    report(pq.top() == 5, "Top should be 5");
    pq.pop();
    report(pq.top() == 10, "Top after popping 5 should be 10");
}

void test_duplicates() {
    PriorityQueue<int> pq;
    std::cout << "\n--- Test Case 4: Duplicate Elements ---\n";
    pq.push(7);
    pq.push(7);
    pq.push(7);
    report(pq.top() == 7, "Top should be 7 with duplicates");
    pq.pop();
    report(pq.top() == 7, "Top after popping 1st 7 should still be 7");
    pq.pop();
    pq.pop();
    report(pq.empty(), "Queue should be empty after popping all duplicates");
}

void test_stress() {
    PriorityQueue<int> pq;
    std::cout << "\n--- Test Case 5: Stress Test with 1000 Elements ---\n";
    for (int i = 1000; i >= 1; --i)
        pq.push(i);

    report(pq.top() == 1, "Top should be 1 after pushing 1000 to 1");

    bool passed = true;
    for (int i = 1; i <= 1000; ++i) {
        if (pq.top() != i) {
            report(false, "Expected top to be " + std::to_string(i));
            passed = false;
            break;
        }
        pq.pop();
    }
    if (passed) report(pq.empty(), "Queue should be empty after popping all 1000 elements");
}

int main() {
    test_basic_push_pop();
    test_sorted_insert();
    test_reverse_insert();
    test_duplicates();
    test_stress();

    std::cout << "\n=== All Tests Finished ===\n";
}
