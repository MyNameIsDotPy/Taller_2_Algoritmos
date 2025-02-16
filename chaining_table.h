#ifndef CHAINING_intABLE_H
#define CHAINING_intABLE_H

#include <iostream>
#include <vector>
#include <optional>
#include <functional>
#include "linked_list.h"
#include "utilities.h"

class ChainingTable {
public:
    LinkedList<int>* table;

    explicit ChainingTable(int m) : m(m) {
        table = new LinkedList<int>[m];
    }

    void insert(int x) {
        int hash = h(x);
        table[hash].prepend(x);
    }

    int h(int k) const {
        return multiplyShiftHash(k, 14) % m;
    }

    std::optional<int> search(int x) const {
        int hash = h(x);
        Node<int>* result = table[hash].search(x);
        return result ? std::optional<int>(result->data) : std::nullopt;
    }

    void remove(int x) const {
        int hash = h(x);
        table[hash].remove(x);
    }

    void show() const {
        for (int i = 0; i < m; i++) {
            std::cout << "[" << i << "]" << " -> ";
            table[i].printList();
        }
    }

private:
    int m;
};

#endif // CHAINING_intABLE_H
