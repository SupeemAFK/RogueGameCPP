#include "LinkListed.h"
#include <iostream>

using namespace std;

template <typename T>
LinkedList<T>::LinkedList() : head(nullptr) {}

template <typename T>
LinkedList<T>::~LinkedList() {
    clearAll();
}

template <typename T>
void LinkedList<T>::insert(const T& value) {
    head = new Node{value, head};
}

template <typename T>
void LinkedList<T>::remove(const T& value) {
    Node* current = head;
    Node* previous = nullptr;

    while (current != nullptr) {
        if (current->data == value) {
            if (previous == nullptr) {
                head = current->next;
            } else {
                previous->next = current->next;
            }
            delete current;
            return;
        }
        previous = current;
        current = current->next;
    }
}

template <typename T>
void LinkedList<T>::clearAll() {
    while (head != nullptr) {
        Node* toDelete = head;
        head = head->next;
        delete toDelete;
    }
}

template <typename T>
void LinkedList<T>::display() const {
    for (Node* current = head; current != nullptr; current = current->next) {
        cout << current->data << " ";
    }
    cout << endl;
}

template class LinkedList<int>;
template class LinkedList<string>;

int main() {
    LinkedList<int> list;  

    while (true) {
        cout << "\nSelect Operations:\n";
        cout << "1. Insert\n";
        cout << "2. Remove\n";
        cout << "3. Display All\n";
        cout << "4. Clear All\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            int value;
            cout << "Enter value to insert: ";
            cin >> value;
            list.insert(value);
            cout << "Inserted value: " << value << endl;
        }
        else if (choice == 2) {
            int value;
            cout << "Enter value to remove: ";
            cin >> value;
            list.remove(value);
            cout << "Removed value: " << value << endl;
        }
        else if (choice == 3) {
            cout << "Displaying all elements in the list: ";
            list.display();
        }
        else if (choice == 4) {
            list.clearAll();
            cout << "Cleared all elements from the list." << endl;
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