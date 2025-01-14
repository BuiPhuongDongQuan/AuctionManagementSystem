#include "Auction.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

// Constructor
Auction::Auction(const Item& item)
    : auctionedItem(item), isAuctionActive(false), highestBid(item.getCurrentBid()), highestBidder("") {}

// Start the auction
void Auction::startAuction() {
    if (isAuctionActive) {
        cout << "Auction for item '" << auctionedItem.getName() << "' is already active!" << endl;
        return;
    }
    isAuctionActive = true;
    cout << "Auction for item '" << auctionedItem.getName() << "' has started!" << endl;
}

// End the auction
void Auction::endAuction() {
    if (!isAuctionActive) {
        cout << "Auction is not active." << endl;
        return;
    }
    isAuctionActive = false;
    cout << "Auction for item '" << auctionedItem.getName() << "' has ended!" << endl;
    if (!highestBidder.empty()) {
        cout << "Winner: " << highestBidder << " with a bid of $" << highestBid << "." << endl;
        // Transfer credit points between buyer and seller
        // This assumes the Member class has credit point management
    } else {
        cout << "No bids were placed for this auction." << endl;
    }
}

// Place a bid
bool Auction::placeBid(const Member& member, int bidAmount) {
    if (!isAuctionActive) {
        cout << "Auction is not active. Unable to place bid." << endl;
        return false;
    }

    if (bidAmount <= highestBid) {
        cout << "Bid must be higher than the current highest bid of $" << highestBid << "." << endl;
        return false;
    }

    highestBid = bidAmount;
    highestBidder = member.getUsername();
    bids[bidAmount] = highestBidder;
    cout << "Bid of $" << bidAmount << " placed by " << highestBidder << "." << endl;

    // Apply automatic bids
    applyAutoBids();

    return true;
}

// Set automatic bid limit
bool Auction::setAutoBidLimit(const Member& member, int bidLimit) {
    if (autoBidLimits.find(member.getUsername()) != autoBidLimits.end() &&
        autoBidLimits[member.getUsername()] == bidLimit) {
        cout << "Automatic bid limit cannot match an existing limit. Please choose a different limit." << endl;
        return false;
    }

    autoBidLimits[member.getUsername()] = bidLimit;
    cout << "Automatic bid limit set to $" << bidLimit << " for " << member.getUsername() << "." << endl;
    return true;
}

// Apply automatic bids
void Auction::applyAutoBids() {
    for (const auto& [username, bidLimit] : autoBidLimits) {
        if (highestBidder != username && highestBid < bidLimit) {
            int nextBid = highestBid + auctionedItem.getBidIncrement();
            if (nextBid <= bidLimit) {
                highestBid = nextBid;
                highestBidder = username;
                bids[nextBid] = username;
                cout << "Automatic bid of $" << nextBid << " placed by " << username << "." << endl;
            }
        }
    }
}

// Display auction details
void Auction::displayAuctionDetails() const {
    cout << "Auction for item: " << auctionedItem.getName() << endl;
    cout << "Current highest bid: $" << highestBid;
    if (!highestBidder.empty()) {
        cout << " by " << highestBidder;
    }
    cout << endl;
    cout << "Auction status: " << (isAuctionActive ? "Active" : "Inactive") << endl;
}

// Ratings and Reviews
void Auction::rateParticipants(Member& seller, Member& buyer, double sellerRating, double buyerRating) {
    seller.rateMember(sellerRating);
    buyer.rateMember(buyerRating);
    cout << "Ratings updated. Seller: " << sellerRating << ", Buyer: " << buyerRating << endl;
}

// Save auction data
void Auction::saveAuctionData(const string& filePath) const {
    ofstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error opening file for saving auction data." << endl;
        return;
    }
    file << auctionedItem.toString() << endl;
    file << isAuctionActive << endl;
    file << highestBid << endl;
    file << highestBidder << endl;
    file.close();
}

// Load auction data
Auction Auction::loadAuctionData(const string& filePath, const vector<Item>& items) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error opening file for loading auction data." << endl;
        throw runtime_error("Could not open auction data file.");
    }
    string line;
    getline(file, line);
    // Match item from items vector based on line (example placeholder)
    Item auctionedItem = items[0];
    bool isAuctionActive;
    int highestBid;
    string highestBidder;

    file >> isAuctionActive >> highestBid >> highestBidder;

    file.close();
    Auction auction(auctionedItem);
    auction.isAuctionActive = isAuctionActive;
    auction.highestBid = highestBid;
    auction.highestBidder = highestBidder;
    return auction;
}
