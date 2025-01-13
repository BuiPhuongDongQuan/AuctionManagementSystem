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

using namespace std;

// Static members
string Item::item_data = "";
vector<Item> Item::items;

// Constructor
Item::Item(string name, string category, string description, int currentBid, int bidIncrement,
           int year, int month, int day, int hour, int minute, int second)
    : name(name), category(category), description(description),
      currentBid(currentBid), bidIncrement(bidIncrement) {
    endDateAndTime = (year * 10000000000LL) + (month * 100000000) + (day * 1000000) +
                     (hour * 10000) + (minute * 100) + second;
}
// New constructor (direct timestamp)
Item::Item(string name, string category, string description, int currentBid, int bidIncrement, long long endDateAndTime)
    : name(name), category(category), description(description),
      currentBid(currentBid), bidIncrement(bidIncrement), endDateAndTime(endDateAndTime) {}

// Set item data file path
void Item::setItemData(string filePath) {
    item_data = filePath;
}

// Read items from data file
void Item::readItemData() {
    items.clear();
    int countLine = Function::countLine(item_data);

    vector<string> itemName = Function::readCol(0, item_data, ';');
    vector<string> category = Function::readCol(1, item_data, ';');
    vector<string> description = Function::readCol(2, item_data, ';');
    vector<string> currentBid = Function::readCol(3, item_data, ';');
    vector<string> bidIncrement = Function::readCol(4, item_data, ';');
    vector<string> endDateAndTime = Function::readCol(5, item_data, ';');

    size_t rowCount = itemName.size();
    if (category.size() != rowCount || description.size() != rowCount || currentBid.size() != rowCount ||
        bidIncrement.size() != rowCount || endDateAndTime.size() != rowCount) {
        cerr << "Error: Columns have inconsistent lengths!" << endl;
        return;
    }

    for (size_t i = 0; i < rowCount; ++i) {
        try {
            // Use the new constructor with timestamp
            items.emplace_back(itemName[i], category[i], description[i], stoi(currentBid[i]),
                               stoi(bidIncrement[i]), stol(endDateAndTime[i]));
        } catch (const exception& e) {
            cerr << "Error processing row " << i << ": " << e.what() << endl;
        }
    }
}

// Add listing
void Item::addListing() {
    string content = toString();
    Function::writeToFile(item_data, content);
    cout << "Item added to file: " << name << endl;
}

// Display full details
void Item::displayDetails() const {
    cout << "Name: " << name << "\n"
         << "Category: " << category << "\n"
         << "Description: " << description << "\n"
         << "Current Bid: " << currentBid << "\n"
         << "Bid Increment: " << bidIncrement << "\n"
         << getShowTime() << endl;
}

// Display limited details
void Item::displayLimitedDetails() const {
    cout << "Name: " << name << " | Category: " << category << " | Description: " << description << endl;
}

// Remove listing
bool Item::removeListing() {
    if (currentBid > 0) {
        cout << "Cannot remove listing. Active bids exist for item: " << name << "." << endl;
        return false;
    }
    cout << "Listing removed for item: " << name << "." << endl;
    return true;
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

// Convert item to string
string Item::toString() const {
    stringstream ss;
    ss << name << ";" << category << ";" << description << ";" << currentBid
       << ";" << bidIncrement << ";" << endDateAndTime << "\n";
    return ss.str();
}

// Getters
string Item::getName() const { return name; }
string Item::getCategory() const { return category; }
string Item::getDescription() const { return description; }
int Item::getCurrentBid() const { return currentBid; }
int Item::getBidIncrement() const { return bidIncrement; }
long long Item::getEndDateAndTime() const { return endDateAndTime; }
string Item::getItemData() { return item_data; }
const vector<Item>& Item::getItems() { return items; }

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

// Update the current bid
void Item::setCurrentBid(int currentBid) {
    this->currentBid = currentBid;
}