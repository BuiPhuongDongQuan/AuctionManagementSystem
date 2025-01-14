#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <vector>
#include <iomanip>
using namespace std;

class Item {
protected:
    static string item_data; // Path to the item data file

private:
    string name;
    string category;
    string description;
    int startingBid; 
    int currentBid;
    int bidIncrement;
    long long endDateAndTime; // Timestamp in YYYYMMDDHHMMSS format
    static vector<Item> items; // Container for all items

public:
    // Constructor
    Item(string name, string category, string description, 
        int startingBid, int currentBid, int bidIncrement, 
        int year, int month, int day, int hour, int minute, int second);
        
    // Methods
    void addListing();
    void displayDetails() const;
    void displayLimitedDetails() const;
    static void readItemData();
    bool isTimerDone() const;
    void startTimer() const;
    bool removeListing();

    // Utility
    string toString() const;
    string getShowTime() const;

    // Getters
    string getName() const;
    string getCategory() const;
    string getDescription() const;
    int getCurrentBid() const;
    int getBidIncrement() const;
    long long getEndDateAndTime() const;
    static string getItemData();
    static const vector<Item>& getItems();

    // Setters
    static void setItemData(string filePath);
    void setCurrentBid(int currentBid);
};

#endif // ITEM_H
