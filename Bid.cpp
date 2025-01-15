#include <iostream>
#include <fstream>
#include <sstream>
#include "Bid.h"
using namespace std;

// Constructor
Bid::Bid(string auctionID = "", string memberID = "", int activeBid = 0, bool isActive = true) 
        : auctionID(auctionID), memberID(memberID), activeBid(activeBid),isActive(isActive) {}

// Check if a member has an active bid in a specific auction
bool Bid::isActiveBid(const string& auctionID, const string& memberID) const {
    return this->auctionID == auctionID && this->memberID == memberID && this->isActive;
}

// Convert bid information to a string for file writing
string Bid::toString() const {
    stringstream ss;
    ss << auctionID << "," << memberID << ","<< activeBid << "," << (isActive ? "true" : "false");
    return ss.str();
}

vector<Bid> Bid::readData(const string& filePath) {
    ifstream inFile(filePath);
    vector<Bid> bids;

    if (!inFile.is_open()) {
        cerr << "Error: Unable to open file for reading.\n";
        return bids;
    }

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string auctionID, memberID, activeStr;
        int activeBid;
        bool isActive;

        getline(ss, auctionID, ',');
        getline(ss, memberID, ',');
        ss >> activeBid;
        ss.ignore(); 
        getline(ss, activeStr);

        isActive = (activeStr == "true");
        bids.emplace_back(auctionID, memberID, isActive);
    }

    inFile.close();
    return bids;
}
