#include <bitset>
#include <iostream>
#include <cstdint>

#include "linked_list.h"


int main() {

    ChainingTable<int> hashMap = ChainingTable<int>(10);

    for (int i = 0; i < 100; i++) {
        hashMap.insert(i);
    }

    for (int i = 0; i<10; i++) {
        hashMap.table[i].printList();
    }

    return 0;
}