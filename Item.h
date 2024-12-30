#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {
private:
    std::string itemName;
    std::string category;
    std::string description;
    int startingBid;
    int bidIncrement;
    long endDateTime; // Use long for simplicity (UNIX timestamp)

public:
    // Constructor
    Item(std::string name, std::string cat, std::string desc, int startBid, int increment, long end);

    // Methods
    void addListing();
    void displayDetails();

    // Getters
    std::string getName() const;
    std::string getCategory() const;
};

#endif // ITEM_H
