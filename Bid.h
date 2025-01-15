#ifndef BID_H
#define BID_H
#include <string>
#include <vector>
using namespace std;

class Bid{
private:
    string auctionID;  // The auction ID
    string memberID;   // The ID of the member placing the bid
    int activeBid;     // Current active bid amount
    bool isActive;     // Whether this bid is active or not
public: 
    Bid(string auctionID, string memberID, int activeBid, bool isActive);

    // Method
    bool isActiveBid(const string& auctionID, const string& memberID) const;
    string toString() const;
    static vector<Bid> readData(const string& filePath);

    // Getters
    string getAuctionID() const;
    string getMemberID() const;
    int getActiveBid() const;
    bool getIsActive() const;
};
#endif