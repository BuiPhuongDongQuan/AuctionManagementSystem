#include "Item.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <chrono>
#include <iomanip>
#include <thread>
#include <ctime>

using namespace std;

// Constructor
Item::Item(string name, string category, string description, int startingBid, int bidIncrement,
           int year, int month, int day, int hour, int minute, int second)
    : name(name), category(category), description(description),
      startingBid(startingBid), bidIncrement(bidIncrement) {
    // Combine the date and time into endDateAndTime (format YYYYMMDDHHMMSS)
    endDateAndTime = (year * 10000000000LL) + (month * 100000000) + (day * 1000000) +
                     (hour * 10000) + (minute * 100) + second;
}

// Add a listing
void Item::addListing() {
    cout << "Listing added: " << name << " in category " << category << "\n";
}

// Display full details
void Item::displayDetails() const {
    cout << "========= ITEM INFORMATION =========\n";
    cout << "Name: " << name << "\n";
    cout << "Category: " << category << "\n";
    cout << "Description: " << description << "\n";
    cout << "Starting Bid: $" << startingBid << "\n";
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
    cout << "Name: " << name << " | Category: " << category << " | Description: " << description << "\n";
}

// Check if timer is done
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

// Timer function
void Item::startTimer() const {
    while (!isTimerDone()) {
        auto now = chrono::system_clock::to_time_t(chrono::system_clock::now());
        struct tm currentTime{};
        localtime_s(&currentTime, &now);

        long long currentDateTime = (currentTime.tm_year + 1900) * 10000000000LL +
                                    (currentTime.tm_mon + 1) * 100000000 +
                                    currentTime.tm_mday * 1000000 +
                                    currentTime.tm_hour * 10000 +
                                    currentTime.tm_min * 100 +
                                    currentTime.tm_sec;

        long long secondsRemaining = endDateAndTime - currentDateTime;

        int hours = secondsRemaining / 3600;
        int minutes = (secondsRemaining % 3600) / 60;
        int seconds = secondsRemaining % 60;

        cout << "\rTime remaining: " << setfill('0') << setw(2) << hours << ":"
             << setfill('0') << setw(2) << minutes << ":"
             << setfill('0') << setw(2) << seconds << "   " << flush;

        this_thread::sleep_for(chrono::seconds(1));
    }

    cout << "\nTime's up for item: " << name << "!\n";
}

// Write item to file
void Item::writeToFile(const string& filePath, const string& content) {
    ofstream file(filePath, ios::app);
    if (!file.is_open()) {
        throw runtime_error("Failed to open file.");
    }
    file << content;
    file.close();
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
    while (getline(file, line)) {
        stringstream ss(line);
        string name, category, description;
        int startingBid, bidIncrement;
        long long endDateAndTime;

        getline(ss, name, ',');
        getline(ss, category, ',');
        getline(ss, description, ',');
        ss >> startingBid;
        ss.ignore();
        ss >> bidIncrement;
        ss.ignore();
        ss >> endDateAndTime;

        int year = endDateAndTime / 10000000000LL;
        int month = (endDateAndTime / 100000000) % 100;
        int day = (endDateAndTime / 1000000) % 100;
        int hour = (endDateAndTime / 10000) % 100;
        int minute = (endDateAndTime / 100) % 100;
        int second = endDateAndTime % 100;

        items.emplace_back(name, category, description, startingBid, bidIncrement,
                           year, month, day, hour, minute, second);
    }

    return items;
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

// Generate item string
string Item::toString() const {
    stringstream ss;
    ss << name << "," << category << "," << description << ","
       << startingBid << "," << bidIncrement << "," << endDateAndTime << "\n";
    return ss.str();
}
