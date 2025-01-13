#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <vector>

class Item {
private:
    std::string name;
    std::string category;
    std::string description;
    int startingBid;
    int bidIncrement;
    long long endDateAndTime; // Timestamp in YYYYMMDDHHMMSS format

public:
    // Constructor
    Item(std::string name = "", std::string category = "", std::string description = "",
         int startingBid = 0, int bidIncrement = 0, int year = 0, int month = 0,
         int day = 0, int hour = 0, int minute = 0, int second = 0);

    // Methods
    void addListing();
    void displayDetails() const;
    void displayLimitedDetails() const;
    bool isTimerDone() const;
    void startTimer() const;

    // File I/O
    static void writeToFile(const std::string& filePath, const std::string& content);
    static std::vector<Item> readData(const std::string& filePath);
    static void removeFromFile(const std::string& filePath, const std::string& itemNameToRemove);

    // Utility
    std::string toString() const;
};

#endif // ITEM_H
