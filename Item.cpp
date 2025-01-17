#include "Item.h"
#include "functions/Function.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <chrono>
#include <iomanip>
#include <thread>
#include <ctime>
#include <algorithm>

using namespace std;

// Static members
string Item::item_data = "";
vector<Item>Item::items;
int Item::nextItemID = 1;
        
// Constructor
Item::Item(int memberID, string name, string category, string description,
           int startingBid, int currentBid, int bidIncrement, double ratePoint, int year, int month, int day,
           int hour, int minute, int second)
    : itemID(nextItemID++), memberID(memberID), name(name), category(category), description(description),
      startingBid(startingBid), currentBid(currentBid), bidIncrement(bidIncrement), ratePoint(ratePoint) {
    endDateAndTime = (year * 10000000000LL) + (month * 100000000) + (day * 1000000) +
                     (hour * 10000) + (minute * 100) + second;
}

Item::Item(int itemID, int memberID, string name, string category, string description,
           int startingBid, int currentBid, int bidIncrement, double ratePoint, int year, int month, int day,
           int hour, int minute, int second)
    : itemID(itemID), memberID(memberID), name(name), category(category), description(description),
      startingBid(startingBid), currentBid(currentBid), bidIncrement(bidIncrement), ratePoint(ratePoint) {
    endDateAndTime = (year * 10000000000LL) + (month * 100000000) + (day * 1000000) +
                     (hour * 10000) + (minute * 100) + second;
    }
// Set item data file path
void Item::setItemData(string filePath) {
    item_data = filePath;
}

// Read items from file
vector<Item> Item::readData(const string& filePath) {
    vector<Item> items;
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error: Could not open file for reading.\n";
        return items;
    }

    string line;
    int maxID = 0;
    while (getline(file, line)) {
        stringstream ss(line);
        string name, category, description;
        int itemID, memberID, startingBid, currentBid, bidIncrement;
        double ratePoint;
        long long endDateAndTime;

        ss >> itemID;
        ss.ignore();
        ss >> memberID;
        ss.ignore();
        getline(ss, name, ',');
        getline(ss, category, ',');
        getline(ss, description, ',');
        ss >> currentBid;
        ss.ignore();
        ss >> bidIncrement;
        ss.ignore();
        ss >> ratePoint;
        ss.ignore();
        ss >> endDateAndTime;

        int year = endDateAndTime / 10000000000LL;
        int month = (endDateAndTime / 100000000) % 100;
        int day = (endDateAndTime / 1000000) % 100;
        int hour = (endDateAndTime / 10000) % 100;
        int minute = (endDateAndTime / 100) % 100;
        int second = endDateAndTime % 100;

        items.emplace_back(itemID, memberID, name, category, description, startingBid, currentBid, bidIncrement, ratePoint,
                           year, month, day, hour, minute, second);
        maxID = max(maxID, itemID);
    }

    nextItemID = maxID + 1;
    return items;
}

// Read items in data file
void Item::readItemData(){
    items.clear();
    int countLine = Function::countLine(item_data);

    vector<string> itemID = Function::readCol(0, item_data, ',');
    vector<string> memberID = Function::readCol(1, item_data, ',');
    vector<string> itemName = Function::readCol(2, item_data, ',');
    vector<string> category = Function::readCol(3, item_data, ',');
    vector<string> description = Function::readCol(4, item_data, ',');
    vector<string> startingBid = Function::readCol(5, item_data, ',');
    vector<string> currentBid = Function::readCol(6, item_data, ',');
    vector<string> bidIncrement = Function::readCol(7, item_data, ',');
    vector<string> ratePoint = Function::readCol(8, item_data, ',');
    vector<string> endDateAndTime = Function::readCol(9, item_data, ',');
    // vector<string> ratingPoints = Function::readCol(7, item_data, ';');

    // Ensure all columns have the same number of elements
    size_t rowCount = itemName.size();
    if (itemID.size() != rowCount ||memberID.size() != rowCount ||category.size() != rowCount || description.size() != rowCount || startingBid.size() != rowCount ||currentBid.size() != rowCount ||
        bidIncrement.size() != rowCount || ratePoint.size() != rowCount || endDateAndTime.size() != rowCount ) { //|| ratingPoints.size() != rowCount
        cerr << "Error: Columns have inconsistent lengths!" << endl;
        return;
    }

    // Populate the users vector with User objects
    for (size_t i = 0; i < rowCount; ++i) { 
        try {
            long long endDateTime = stol(endDateAndTime[i]);
            int year = endDateTime / 10000000000LL;
            int month = (endDateTime / 100000000) % 100;
            int day = (endDateTime / 1000000) % 100;
            int hour = (endDateTime / 10000) % 100;
            int minute = (endDateTime / 100) % 100;
            int second = endDateTime % 100;
            
            items.emplace_back(stoi(itemID[i]), stoi(memberID[i]), itemName[i], category[i], description[i], 
                            stoi(startingBid[i]), stoi(currentBid[i]), stoi(bidIncrement[i]),  stod(ratePoint[i]), 
                            year, month, day, hour, minute, second);
        } catch (const exception& e) {
            cerr << "Error processing row " << i << ": " << e.what() << endl;
            continue;  // Skip this row and continue with the next one
        }
    }
}

// Write item to file
void Item::writeToFile(const string& filePath, const string& content) {
    ofstream file(filePath, ios::app);
    if (!file.is_open()) {
        cerr << "Error: Could not open file '" << filePath << "' for writing.\n";
        perror("Error");
        return;
    }

    file << content << endl;
    if (file.fail()) {
        cerr << "Error: Failed to write to file '" << filePath << "'.\n";
    } else {
        cout << "Successfully wrote item to file: " << filePath << endl;
    }

    file.close();
}


// Remove items by name from file
void Item::removeFromFile(const string& filePath, const string& itemNameToRemove) {
    vector<Item> items = readData(filePath);
    ofstream file(filePath, ios::trunc);
    if (!file.is_open()) {
        throw runtime_error("Error: Could not open file for writing.");
    }

    for (const auto& item : items) {
        if (item.name != itemNameToRemove) {
            file << item.toString();
        }
    }
    file.close();
}

void Item::updateDataFile(const string& filePath) {
    ofstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error opening file for updating item data.\n";
        return;
    }

    for (const auto& item : items) {
        file << item.itemID << "," << item.memberID << "," << item.name << "," << item.category << ","
             << item.description << "," << item.startingBid << "," << item.currentBid << "," << item.bidIncrement << ","
             << item.endDateAndTime << "\n";
    }

    file.close();
    cout << "Item data updated successfully.\n";
}

bool Item::updateCurrentBidByID(const int itemID, int newBid) {
    for (auto& item : items) {
        if (item.getItemID() == itemID) {
            if (newBid > item.currentBid) {
                item.currentBid = newBid;
                cout << "Updated current bid for item ID: " << itemID << " to $" << newBid << endl;
                updateDataFile(item_data);
                return true;
            } else {
                cout << "New bid must be higher than the current bid.\n";
                return false;
            }
        }
    }
    cout << "Item with ID " << itemID << " not found.\n";
    return false;
}

// Generate item string
string Item::toString() const {
    stringstream ss;
    ss << itemID << "," << memberID << "," << name << "," << category << "," << description << ","
       << startingBid << "," << currentBid << "," << bidIncrement << "," << ratePoint << "," << endDateAndTime << "\n";

    return ss.str();
}


// Add listing
void Item::addListing() {
    string content = toString();
    Function::writeToFile(item_data, content);
    cout << "Item added to file: " << name << endl;
}

// Display full details
void Item::displayDetails() const {
    cout << "========= ITEM INFORMATION =========\n";
    cout << "Name: " << name << "\n";
    cout << "Category: " << category << "\n";
    cout << "Description: " << description << "\n";
    cout << "Starting Bid: $" << currentBid << "\n";
    cout << "Increment Bid: $" << bidIncrement << "\n";

    int year = endDateAndTime / 10000000000LL;
    int month = (endDateAndTime / 100000000) % 100;
    int day = (endDateAndTime / 1000000) % 100;
    int hour = (endDateAndTime / 10000) % 100;
    int minute = (endDateAndTime / 100) % 100;
    int second = endDateAndTime % 100;

    cout << "Due Date: " << year << "-" << setw(2) << setfill('0') << month << "-"
         << setw(2) << setfill('0') << day << "\n";
    cout << "Due Time: " << setw(2) << setfill('0') << hour << ":"
         << setw(2) << setfill('0') << minute << ":"
         << setw(2) << setfill('0') << second << "\n";
    cout << "====================================\n";
}

// Display limited details
void Item::displayLimitedDetails() const {
    cout << "Name: " << name << " | Category: " << category << " | Description: " << description << endl;
}

// Timer-related functions
bool Item::isTimerDone() const {
    auto now = chrono::system_clock::to_time_t(chrono::system_clock::now());
    struct tm currentTime{};
    localtime_s(&currentTime, &now);

    long long currentDateTime = (currentTime.tm_year + 1900) * 10000000000LL +
                                (currentTime.tm_mon + 1) * 100000000 +
                                currentTime.tm_mday * 1000000 +
                                currentTime.tm_hour * 10000 +
                                currentTime.tm_min * 100 +
                                currentTime.tm_sec;

    return currentDateTime >= endDateAndTime;
}

void Item::startTimer() const {
    while (!isTimerDone()) {
        this_thread::sleep_for(chrono::seconds(1));
        cout << "\rTime remaining: ..." << flush; // Simplified for brevity
    }
    cout << "\nTime's up for item: " << name << "!" << endl;
}

// Remove listing
bool Item::removeListing() {
    if (currentBid > 0) {
        cout << "Cannot remove listing. Active bids exist for item: " << name << ".\n";
        return false;
    }
    cout << "Listing '" << name << "' removed successfully.\n";
    return true;
}


// Getters
int Item::getItemID() const { return itemID; }
int Item::getMemberID() const { return memberID; }
string Item::getName() const { return name; }
string Item::getCategory() const { return category; }
string Item::getDescription() const {return description;}
string Item::getItemData() {return item_data;}
int Item::getCurrentBid() const{ return currentBid; };
int Item::getBidIncrement() const{ return bidIncrement; };
double Item::getRatePoint() const {return ratePoint;}
const vector<Item>& Item::getItems() {return items;}
// Convert timestamp to human-readable date and time
string Item::getShowTime() const {
    stringstream ss;
    int year = endDateAndTime / 10000000000LL;
    int month = (endDateAndTime / 100000000) % 100;
    int day = (endDateAndTime / 1000000) % 100;
    int hour = (endDateAndTime / 10000) % 100;
    int minute = (endDateAndTime / 100) % 100;
    int second = endDateAndTime % 100;
    ss << year << "-" << setw(2) << setfill('0') << month << "-"
       << setw(2) << setfill('0') << day << " "
       << setw(2) << setfill('0') << hour << ":"
       << setw(2) << setfill('0') << minute << ":"
       << setw(2) << setfill('0') << second;

    return ss.str();
}
void Item::removeItem(const int itemID) {
    items.erase(remove_if(items.begin(), items.end(),
                          [&itemID](const Item& item) { return item.getItemID() == itemID; }),
                items.end());
    cout << "Item with ID " << itemID << " has been removed from the system.\n";
}

void Item::setRatePoint(double ratePoint) {
    if (ratePoint < 0 || ratePoint > 5) {
        cerr << "Error: Rate point must be between 0 and 5.\n";
        return;
    }
    this->ratePoint = ratePoint;
    cout << "Rate point for item ID " << itemID << " set to " << ratePoint << endl;
}

bool Item::isVisibleTo(double buyerRating) const {
    return buyerRating >= ratePoint;
}

vector<Item> Item::getVisibleItems(double buyerRating) {
    vector<Item> visibleItems;
    for (const auto& item : items) {
        if (item.isVisibleTo(buyerRating)) {
            visibleItems.push_back(item);
        }
    }
    return visibleItems;
}

void Item::displayItems(const vector<Item>& items) {
    for (const auto& item : items) {
        cout << "Item ID: " << item.getItemID() << ", Name: " << item.getName()
             << ", Minimum Rating: " << item.getRatePoint() << endl;
    }
}

// Update the current bid
void Item::setCurrentBid(int currentBid) {
    this->currentBid = currentBid;
}
