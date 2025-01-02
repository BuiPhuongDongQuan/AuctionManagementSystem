#include "Item.h"
#include "functions/Function.h"
#include <iostream>
using namespace std;

// Static members
string Item::item_data = "";
vector<Item>Item::items;

// Constructor
Item::Item(std::string name, std::string cat, std::string desc, int startBid, int increment, long end, double ratingPoints)
    : itemName(name), category(cat), description(desc), startingBid(startBid), bidIncrement(increment), endDateTime(end), ratingPoints(ratingPoints){}

// Set item data file path
void Item::setItemData(string filePath){
    item_data = filePath;
}

// Read items in data file
void Item::readItemData(){
    items.clear();
    int countLine = Function::countLine(item_data);

    vector<string> itemName = Function::readCol(0, item_data, ';');
    vector<string> category = Function::readCol(1, item_data, ';');
    vector<string> description = Function::readCol(2, item_data, ';');
    vector<string> startingBid = Function::readCol(3, item_data, ';');
    vector<string> bidIncrement = Function::readCol(4, item_data, ';');
    vector<string> endDateAndTime = Function::readCol(5, item_data, ';');
    vector<string> ratingPoints = Function::readCol(6, item_data, ';');

    // Ensure all columns have the same number of elements
    size_t rowCount = itemName.size();
    if (category.size() != rowCount || description.size() != rowCount || startingBid.size() != rowCount ||
        bidIncrement.size() != rowCount || endDateAndTime.size() != rowCount || ratingPoints.size() != rowCount) {
        std::cerr << "Error: Columns have inconsistent lengths!" << std::endl;
        return;
    }

    // Populate the users vector with User objects
    for (size_t i = 0; i < rowCount; ++i) { 
        try {
            items.emplace_back(itemName[i], category[i], description[i], stoi(startingBid[i]), stoi(bidIncrement[i]), 
                               stol(endDateAndTime[i]), stod(ratingPoints[i]));
        } catch (const std::exception& e) {
            std::cerr << "Error processing row " << i << ": " << e.what() << std::endl;
            continue;  // Skip this row and continue with the next one
        }
    }
}

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
string Item::getDescription() const {return description;}
string Item::getItemData() {return item_data;}
const vector<Item>& Item::getItems() {return items;}