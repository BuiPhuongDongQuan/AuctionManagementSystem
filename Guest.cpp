#include "Guest.h"
#include "Item.h"
#include <iostream>
using namespace std;

Guest::Guest() : User() {}

void Guest::viewItem() const {
    // Ensure the item data is loaded into the static vector
    Item::readItemData();

    // Access the static vector of items
    const auto& items = Item::getItems();

    // Check if there are any items available
    if (items.empty()) {
        cerr << "No items available!" << endl;
        return;
    }

    // Display items with the required fields
    cout << "Available items:\n";
    for (const auto& item : items) {
        cout << "Item Name: " << item.getName() << endl;
        cout << "Category: " << item.getCategory() << endl;
        cout << "Description: " << item.getDescription() << endl;
        cout << "----------------------\n";
    }
}