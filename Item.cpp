#include "Item.h"
#include <iostream>

// Constructor
Item::Item(std::string name, std::string cat, std::string desc, int startBid, int increment, long end)
    : itemName(name), category(cat), description(desc), startingBid(startBid), bidIncrement(increment), endDateTime(end) {}

// Add a listing
void Item::addListing() {
    std::cout << "Listing added: " << itemName << " in category " << category << "\n";
}

// Display details
void Item::displayDetails() {
    std::cout << "Item Name: " << itemName << "\nCategory: " << category
              << "\nDescription: " << description
              << "\nStarting Bid: " << startingBid
              << "\nBid Increment: " << bidIncrement
              << "\nEnd Time (timestamp): " << endDateTime << "\n";
}

// Getters
std::string Item::getName() const { return itemName; }
std::string Item::getCategory() const { return category; }
