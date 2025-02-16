//
// Created by 0srma on 4/02/2025.
//

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

template <typename T>
class Node {
public:
    T data;
    Node* next;
    Node* previous;
    Node(T d) : data(d), next(nullptr), previous(nullptr) {}
};

template <typename T>
class LinkedList {
    public:
    LinkedList() : head(nullptr), tail(nullptr) {}

    public:
    Node<T>* prepend(T value) {
        Node<T>* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
            return newNode;
        }
        newNode->next = head;
        head->previous = newNode;
        head = newNode;
        return newNode;
    };

    Node<T>* append(T value) {
        if (head == nullptr) {
            return prepend(value);
        }
        Node<T>* newNode = new Node<T>(value);
        Node<T>* currentNode = head;
        while (currentNode->next != nullptr) {
            currentNode = currentNode->next;
        }
        currentNode->next = newNode;
        newNode->previous = currentNode;
        return newNode;
    }

    Node<T>* search(T value) const {
        Node<T>* currentNode = head;
        while (currentNode != nullptr) {
            if (currentNode->data == value) {
                return currentNode;
            }
            currentNode = currentNode->next;
        }
        return nullptr;
    }

    bool remove(T x) {
        Node<T>* node = search(x);
        return removeNode(node);
    }

    bool removeNode(Node<T>* node) {
        if (node == nullptr) return false;

        if (node == head) {
            head = head->next;
            if (head != nullptr) {
                head->previous = nullptr;
            } else {
                tail = nullptr; // List is now empty
            }
        } else if (node == tail) {
            tail = tail->previous;
            if (tail != nullptr) {
                tail->next = nullptr;
            } else {
                head = nullptr; // List is now empty
            }
        } else {
            Node<T>* previousNode = node->previous;
            Node<T>* nextNode = node->next;
            if (previousNode != nullptr) {
                previousNode->next = nextNode;
            }
            if (nextNode != nullptr) {
                nextNode->previous = previousNode;
            }
        }

        delete node;
        return true;
    }

    void printList() {
        Node<T>* current = head;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }


private:
    Node<T>* head;
    Node<T>* tail;
};


#endif //LINKED_LIST_H
