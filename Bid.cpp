#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>
#include "Bid.h"
using namespace std;

// Constructor
Bid::Bid(string auctionID, int memberID, int activeBid, bool isActive) 
        : auctionID(auctionID), memberID(memberID), activeBid(activeBid),isActive(isActive) {}

// Convert bid information to a string for file writing
string Bid::toString() const {
    stringstream ss;
    ss << auctionID << "," << memberID << ","<< activeBid << "," << "true";
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
        string auctionID, activeStr;
        int activeBid, memberID;
        bool isActive;

        getline(ss, auctionID, ',');
        ss >> memberID;
        ss.ignore(); 
        ss >> activeBid;
        ss.ignore();  
        getline(ss, activeStr);

        isActive = (activeStr == "true");
        bids.emplace_back(auctionID, memberID, activeBid, isActive);
    }

    inFile.close();
    return bids;
}

// Check if a member has an active bid in a specific auction
bool Bid::isActiveBid(const string& auctionID, int memberID, const string& filePath){
    ifstream inFile(filePath);
    if (!inFile.is_open()) {
        throw runtime_error("Error: Could not open file " + filePath);
    }

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string fileAuctionID, activeStr;
        int activeBid, fileMemberID;
        bool isActive;

        getline(ss, fileAuctionID, ',');
        ss >> fileMemberID;
        ss.ignore(); 
        ss >> activeBid;
        ss.ignore(); 
        getline(ss, activeStr);
        
        // Check if auctionID and memberID match
        if (fileMemberID == memberID && fileAuctionID == auctionID) {
            inFile.close();
            return true;
        }
    }

    inFile.close();
    return false;
}

int Bid::calculateBidDifference(int memberID, int newBid, std::unordered_map<std::string, int>& previousBids) {
    int difference = 0;

    string memberIDStr = to_string(memberID);
    // Check if the user has a previous bid
    if (previousBids.find(memberIDStr) != previousBids.end()) {
        difference = newBid - previousBids[memberIDStr];
    }

    // Update the previous bid for the user
    previousBids[memberIDStr] = newBid;

    return difference;
}

// Getters
string Bid::getAuctionID() const { return auctionID; }
int Bid::getActiveBid() const { return activeBid; }
bool Bid::getIsActive() const { return isActive; }

// Setters
void Bid::setIsActive(bool isActive) {
    this -> isActive = isActive;
}

void Bid::setActiveBid(int activeVid){
    this -> activeBid = activeBid;
}

