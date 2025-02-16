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
        deleted = new bool[m]; // Tracks deleted slots

        for (int i = 0; i < m; i++) {
            table[i] = nullptr;
            deleted[i] = false;
        }
    }

    ~LinearProbingTable() {
        for (int i = 0; i < m; i++) {
            if (table[i] != nullptr) {
                delete table[i];  // Free memory of stored integers
            }
        }
        delete[] table;   // Free table itself
        delete[] deleted; // Free deletion tracking array
    }

    void insert(int key) {
        int i = 0;
        int q;
        int deletedSlot = -1;  // Track first available deleted slot

        do {
            q = h(key, i);
            if (q < 0 || q >= m) return; // Prevent out-of-bounds access

            if (table[q] == nullptr) {  // Found empty slot
                if (deletedSlot != -1) {
                    table[deletedSlot] = new int(key);  // Reuse deleted slot
                    deleted[deletedSlot] = false;  // Mark as active
                } else {
                    table[q] = new int(key);  // Insert in empty slot
                }
                return;
            }
            if (deleted[q] && deletedSlot == -1) {
                deletedSlot = q;  // Store first deleted slot
            } else if (table[q] != nullptr && *table[q] == key) {
                return;  // Key already exists, do nothing
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
            if (q < 0 || q >= m) return nullptr; // Prevent out-of-bounds access

            if (table[q] == nullptr) return nullptr;  // Stop if empty slot is reached
            if (!deleted[q] && table[q] != nullptr && *table[q] == key) return table[q];  // Found key
            i++;
        } while (i < m);
        return nullptr;
    }

    bool remove(int key) {
        int i = 0;
        int q;
        do {
            q = h(key, i);
            if (q < 0 || q >= m) return false; // Prevent out-of-bounds access

            if (table[q] == nullptr) return false;  // Key not found
            if (!deleted[q] && table[q] != nullptr && *table[q] == key) {
                delete table[q];  // Free memory
                table[q] = nullptr;  // Mark as empty
                deleted[q] = true;  // Mark slot as deleted
                return true;
            }
            i++;
        } while (i < m);
        return false;
    }

    int h(int k, int i) const {
        return (multiplyShiftHash(k, 14) + i) % m;  // Linear probing function
    }

    void show() {
        for (int i = 0; i < m; i++) {
            if (table[i] == nullptr) {
                std::cout << "[" << i << "] -> " << (deleted[i] ? "DELETED" : "EMPTY") << std::endl;
            } else {
                std::cout << "[" << i << "] -> " << *table[i] << std::endl;
            }
        }
    }

private:
    int** table;  // Array of int pointers
    bool* deleted;  // Array to track deleted slots
    int m;
};

#endif // LINEAR_PROBING_TABLE_H
