#ifndef ITEM_H
#define ITEM_H
#include <string>
#include <vector>

class Item {
protected:
    static string item_data;
private:
    std::string name;
    std::string category;
    std::string description;
    int startingBid;
    int bidIncrement;
    long long endDateAndTime; // Timestamp in YYYYMMDDHHMMSS format
    static vector<Item> items;

public:
    // Constructor
    Item(std::string name = "", std::string category = "", std::string description = "",
         int startingBid = 0, int bidIncrement = 0, int year = 0, int month = 0,
         int day = 0, int hour = 0, int minute = 0, int second = 0);

    // Methods
    void addListing();
    void displayDetails() const;
    void displayLimitedDetails() const;
    static void readItemData();
    static void setItemData(string filePath);
    bool isTimerDone() const;
    void startTimer() const;

    // File I/O
    static void writeToFile(const std::string& filePath, const std::string& content);
    static std::vector<Item> readData(const std::string& filePath);
    static void removeFromFile(const std::string& filePath, const std::string& itemNameToRemove);

    // Utility
    std::string toString() const;

    // Getters
    std::string getName() const;
    std::string getCategory() const;
    string getDescription()const;
    static string getItemData();
    static const vector<Item>& getItems();
};

#endif // ITEM_H