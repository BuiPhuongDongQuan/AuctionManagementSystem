#include "Item.h"
#include <iostream>

// Constructor
Item::Item(std::string name, std::string cat, std::string desc, int startBid, int increment, time_t end, Member* sellerRef, float rating)
    : itemName(name), category(cat), description(desc), startingBid(startBid), bidIncrement(increment),
      endDateTime(end), seller(sellerRef), ratingScore(rating), currentBid(0), highestBidder(nullptr) {}

// Add listing
void Item::addListing() {
    std::cout << "Item '" << itemName << "' listed in category '" << category << "' with starting bid of " << startingBid << " CP.\n";
}

// Remove listing
bool Item::removeListing() {
    if (currentBid > 0) {
        std::cout << "Cannot remove listing. Active bids exist for item: " << itemName << ".\n";
        return false;
    }
    std::cout << "Listing '" << itemName << "' removed successfully.\n";
    return true;
}

// Display limited details
void Item::displayLimitedDetails() {
    std::cout << "Item: " << itemName << " | Category: " << category << " | Description: " << description << "\n";
}

// Display full details
void Item::displayFullDetails() {
    std::cout << "Item: " << itemName << "\nCategory: " << category
              << "\nDescription: " << description
              << "\nStarting Bid: " << startingBid
              << "\nCurrent Bid: " << (currentBid > 0 ? std::to_string(currentBid) : "No bids yet")
              << "\nMinimum Buyer Rating: " << ratingScore << "\n";
}

// Place bid
bool Item::placeBid(Member* bidder, int bidAmount) {
    if (bidAmount < startingBid || (currentBid > 0 && bidAmount < currentBid + bidIncrement)) {
        std::cout << "Bid too low. Minimum increment is: " << bidIncrement << " CP.\n";
        return false;
    }

    highestBidder = bidder;
    currentBid = bidAmount;
    std::cout << "Bid placed successfully by " << bidder->getUsername() << " for " << bidAmount << " CP.\n";
    return true;
}

// Getters
std::string Item::getName() const { return itemName; }
std::string Item::getCategory() const { return category; }
int Item::getCurrentBid() const { return currentBid; }
time_t Item::getEndDateTime() const { return endDateTime; }
