#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <vector>
#include <iomanip>
using namespace std;

class Item {
protected:
    static string item_data;
    static int nextItemID;

private:
    int itemID;
    int memberID;
    string name;
    string category;
    string description;
    int startingBid;
    int currentBid;
    int bidIncrement;
    long long endDateAndTime; // Timestamp in YYYYMMDDHHMMSS format
    double ratePoint;
    static vector<Item> items;


public:
    // Constructor
    Item(int memberID, string name, string category, string description,
         int startingBid, int currentBid, int bidIncrement, double ratePoint, int year, int month, int day,
         int hour, int minute, int second);

    Item(int itemID, int memberID, string name, string category, string description,
         int startingBid, int currentBid, int bidIncrement, double ratePoint, int year, int month, int day,
         int hour, int minute, int second);
    // Methods
    static bool updateCurrentBidByID(const int itemID, int newBid);
    void addListing();
    void displayDetails() const;
    void displayLimitedDetails() const;
    static void readItemData();
    bool isTimerDone() const;
    void startTimer() const;
    bool removeListing();
    bool isVisibleTo(double buyerRating) const;
    static vector<Item> getVisibleItems(double buyerRating);
    static void displayItems(const vector<Item>& items);

    // File I/O
    static void writeToFile(const string& filePath, const string& content);
    static vector<Item> readData(const string& filePath);
    static void removeFromFile(const string& filePath, const string& itemNameToRemove);
    static void updateDataFile(const string& filePath);
    static void removeItem(const int itemID);

    // Utility
    string toString() const;
    string getShowTime() const;

    // Getters
    int getItemID() const;
    int getMemberID() const;
    string getName() const;
    string getCategory() const;
    string getDescription() const;
    int getCurrentBid() const;
    int getBidIncrement() const;
    double getRatePoint() const;
    long long getEndDateAndTime() const;
    static string getItemData();
    static const vector<Item>& getItems();

    // Setters
    static void setItemData(string filePath);
    void setCurrentBid(int currentBid);
    void setRatePoint(double ratePoint);
};

#endif // ITEM_H
