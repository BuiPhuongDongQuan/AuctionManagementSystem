#include "Item.h"
#include <iostream>
#include <ctime> // For time manipulation

void testItemClass() {
    // Set up
    long endTime = time(nullptr) + 86400; // 1 day later
    Item item("Laptop", "Electronics", "High-end gaming laptop", 500, 50, endTime);

    // Test addListing()
    std::cout << "=== Test addListing ===\n";
    item.addListing();

    // Test displayDetails()
    std::cout << "\n=== Test displayDetails ===\n";
    item.displayDetails();
}

int main() {
    testItemClass();
    return 0;
}
