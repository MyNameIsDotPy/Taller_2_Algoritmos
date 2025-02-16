#include "chaining_table.h"
#include "linear_probing_table.h"
#include "linked_list.h"


int main() {

    LinearProbingTable table(7);

    table.insert(10);
    table.insert(20);
    table.insert(15);
    table.insert(7);
    table.insert(9);
    table.insert(16);
    table.insert(8);
    table.insert(1);
    table.insert(2);
    table.insert(3);

    table.show();

    table.remove(10);
    table.remove(15);
    table.remove(9);
    table.remove(8);

    table.show();

    table.insert(10);
    std::cout << "Showing" << std::endl;
    table.show();


    int* found = table.search(15);
    if (found) {
        std::cout << "Found: " << *found << std::endl;
    } else {
        std::cout << "Not Found" << std::endl;
    }

    int* notFound = table.search(99);
    if (notFound) {
        std::cout << "Found: " << *notFound << std::endl;
    } else {
        std::cout << "Not Found" << std::endl;
    }

    return 0;
}