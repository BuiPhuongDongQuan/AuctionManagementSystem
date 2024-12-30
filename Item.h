#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <ctime>
#include "Member.h" // Include Member class

class Item {
private:
    std::string itemName;
    std::string category;
    std::string description;
    int startingBid;
    int bidIncrement;
    time_t endDateTime;
    Member* seller;
    float ratingScore;
    int currentBid;
    Member* highestBidder;

public:
    // Constructor
    Item(std::string name, std::string cat, std::string desc, int startBid, int increment, time_t end, Member* sellerRef, float rating);

    // Methods
    void addListing();
    bool removeListing();
    void displayLimitedDetails();
    void displayFullDetails();
    bool placeBid(Member* bidder, int bidAmount);

    // Getters
    std::string getName() const;
    std::string getCategory() const;
    int getCurrentBid() const;
    time_t getEndDateTime() const;
};

#endif // ITEM_H
