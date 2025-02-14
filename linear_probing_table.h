//
// Created by 0srma on 13/02/2025.
//

#ifndef LINEAR_PROBING_TABLE_H
#define LINEAR_PROBING_TABLE_H
#include "utilities.h"
#include <iostream>

class LinearProbingTable {
public:
    explicit LinearProbingTable(int m) : m(m) {
        table = new int*[m];  // Array of int* (pointers), initialized to nullptr
        for (int i = 0; i < m; i++) {
            table[i] = nullptr;
        }
    }

    ~LinearProbingTable() {
        for (int i = 0; i < m; i++) {
            delete table[i];  // Free memory of stored integers
        }
        delete[] table;  // Free table itself
    }

    void insert(int key) {
        int i = 0;
        int q;
        do {
            q = h(key, i);
            if (table[q] == nullptr) {
                table[q] = new int(key);  // Allocate new integer
                return;
            }
            i++;
        } while (i < m);
        std::cout << "Table is full, cannot insert key: " << key << std::endl;
    }

    int* search(int key) {
        int i = 0;
        int q;
        do {
            q = h(key, i);
            if (table[q] == nullptr) return nullptr;  // Stop if empty slot is reached
            if (*table[q] == key) return table[q];  // Return pointer to found key
            i++;
        } while (i < m);
        return nullptr;
    }

    int h(int k, int i) const {
        return (multiplyShiftHash(k, 14) + 1) % m;  // Linear probing function
    }

    void show() {
        for (int i = 0; i < m; i++) {
            if (table[i] != nullptr) {
                std::cout << "[" << i << "] -> " << *table[i] << std::endl;
            } else {
                std::cout << "[" << i << "] -> EMPTY" << std::endl;
            }
        }
    }

private:
    int** table;  // Array of int pointers
    int m;
};

#endif // LINEAR_PROBING_TABLE_H