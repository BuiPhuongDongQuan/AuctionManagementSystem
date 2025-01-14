#ifndef AUCTION_H
#define AUCTION_H

#include "Item.h"
#include "Member.h"
#include <map>
#include <string>
#include <vector>

class Auction {
private:
    Item auctionedItem;                        // The item being auctioned
    std::map<int, std::string> bids;           // Bids: {bidAmount -> bidderUsername}
    std::map<std::string, int> autoBidLimits;  // Automatic bid limits: {username -> bidLimit}
    bool isAuctionActive;                      // Status of the auction
    int highestBid;                            // Current highest bid
    std::string highestBidder;                 // Username of the highest bidder

    // Helper functions
    void applyAutoBids();

public:
    // Constructor
    Auction(const Item& item);

    // Auction Management
    void startAuction();
    void endAuction();
    bool placeBid(const Member& member, int bidAmount);
    bool setAutoBidLimit(const Member& member, int bidLimit);

    // Auction Details
    void displayAuctionDetails() const;
    int getHighestBid() const;
    std::string getHighestBidder() const;
    bool isActive() const;

    // Ratings and Reviews
    void rateParticipants(Member& seller, Member& buyer, double sellerRating, double buyerRating);

    // Data Management
    void saveAuctionData(const std::string& filePath) const;
    static Auction loadAuctionData(const std::string& filePath, const std::vector<Item>& items);
};

#endif // AUCTION_H
