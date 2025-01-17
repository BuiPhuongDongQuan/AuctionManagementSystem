#ifndef MEMBER_H
#define MEMBER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "Bid.h"
#include "User.h"
using namespace std;

class Item; 

class Rating;

class Member : public User{
private:
    static int nextID;
    string memberID;
    string username;
    string password;
    string fullname;
    string phoneNumber;
    string email;
    string IDType;
    string IDNumber;
    double rating;
    int ratingCount;
    int creditPoints;

    vector<Item> listings;
    vector<Bid> activeBids;

public:
    Member();
    Member(string memberID, string username, string password, string fullname, string phoneNumber, 
           string email, string IDType, string IDNumber, double rating , int ratingCount, int creditPoint);

    // Method
    void login(string username, string password);
    void showInfo(string username);
    void updateInfo(int userInput, string username);
    void topupCredit(string username);
    void createListing(string username);
    void rateMember(double ratingValue);
    void updateItemInFile(const string& filePath, const Item& updatedItem);
    void updateMemberInFile(const string& filePath);
    int balanceCP()const;
    bool placeBid(const string& auctionID, int bidAmount);
    void finalizeBid(const string& auctionID, bool won);
    void viewListings(const string& filePath);
    void searchItems(const string& name, const string& category, int minBid, int maxBid);
    string toLower(const string& str);

    // Getters
    vector<Item> getListings() const;


};

#endif
