#ifndef CHAINING_TABLE_H
#define CHAINING_TABLE_H

#include <iostream>
#include "linked_list.h"
#include "utilities.h"

template <typename T>
class ChainingTable {
public:
    LinkedList<T>* table;

    explicit ChainingTable(int m) : m(m) {
        table = new LinkedList<T>[m];
    }

    ~ChainingTable() {
        delete[] table;
    }

    void insert(T x) {
        int hash = h2(x);
        table[hash].prepend(x);
    }

    T search(T x) {
        int hash = h2(x);
        return table[hash].search(x);
    }

    void remove(T x) {
        int hash = h2(x);
        table[hash].deleteNode(x);
    }

    int h(const T& value) {
        std::size_t hashValue = std::hash<T>{}(value);
        std::cout << "Value " << value << " Hashed into " << (hashValue % m) << std::endl;
        return static_cast<int>(hashValue % m);
    }

    int h2(int k) const {
        return multiplyShiftHash(k, 14) % m;
    }

private:
    int m; // Tamaño de la tabla hash
};

#endif // CHAINING_TABLE_H