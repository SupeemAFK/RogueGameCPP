#include <iostream>
#include "PriorityQueue.h"
#include <functional>
#include <cstdlib> // เพิ่มตรงนี้ สำหรับ system()

void clearScreen() {
#ifdef _WIN32
    system("CLS");
#else
    system("clear");
#endif
}

void printMenu() {
    std::cout << "\n--- PriorityQueue Menu ---\n";
    std::cout << "1. Push a value\n";
    std::cout << "2. Pop top value\n";
    std::cout << "3. Show top value\n";
    std::cout << "4. Show size\n";
    std::cout << "5. Check if empty\n";
    std::cout << "6. Show all elements\n";
    std::cout << "7. Exit\n";
    std::cout << "Choose an option: ";
}

template<typename T, typename Compare>
void printAllElements(PriorityQueue<T, Compare> pq) {
    std::cout << "Elements in the PriorityQueue: ";
    while (!pq.empty()) {
        std::cout << pq.top() << " ";
        pq.pop();
    }
    std::cout << "\n";
}

int main() {
    PriorityQueue<int> pq; // min-heap by default

    int choice;
    do {
        clearScreen();
        printMenu();
        std::cin >> choice;

        switch (choice) {
            case 1: {
                int value;
                std::cout << "Enter value to push: ";
                std::cin >> value;
                pq.push(value);
                std::cout << "Pushed " << value << " into the queue.\n";
                break;
            }
            case 2: {
                try {
                    pq.pop();
                    std::cout << "Popped top value.\n";
                } catch (const std::runtime_error& e) {
                    std::cout << "Error: " << e.what() << "\n";
                }
                break;
            }
            case 3: {
                try {
                    int topValue = pq.top();
                    std::cout << "Top value: " << topValue << "\n";
                } catch (const std::runtime_error& e) {
                    std::cout << "Error: " << e.what() << "\n";
                }
                break;
            }
            case 4:
                std::cout << "Current size: " << pq.size() << "\n";
                break;
            case 5:
                if (pq.empty())
                    std::cout << "PriorityQueue is empty.\n";
                else
                    std::cout << "PriorityQueue is not empty.\n";
                break;
            case 6:
                printAllElements(pq);
                break;
            case 7:
                std::cout << "Exiting.\n";
                break;
            default:
                std::cout << "Invalid option. Please try again.\n";
        }

        if (choice != 7) {
            std::cout << "\nPress Enter to continue...";
            std::cin.ignore();
            std::cin.get();
        }

    } while (choice != 7);

    return 0;
}
