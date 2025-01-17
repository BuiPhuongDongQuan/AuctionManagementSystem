#ifndef BID_H
#define BID_H
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Bid{
private:
    string auctionID;  // The auction ID
    int memberID;   // The ID of the member placing the bid
    int activeBid;     // Current active bid amount
    bool isActive;     // Whether this bid is active or not
public: 
    Bid(): auctionID(""), memberID(0), isActive(false) {};
    Bid(string auctionID, int memberID, int activeBid, bool isActive);

    // Method
    bool isActiveBid(const string& auctionID, int memberID, const string& filePath);
    string toString() const;
    static vector<Bid> readData(const string& filePath);
    static int calculateBidDifference(int memberID, int newBid, unordered_map<string, int>& previousBids);

    // Getters
    string getAuctionID() const;
    int getMemberID() const;
    int getActiveBid() const;
    bool getIsActive() const;

    // Setters
    void setIsActive(bool isActive); 
    void setActiveBid(int activeVid);
};
#endif