#ifndef MEMBER_H
#define MEMBER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

class Item; 

class Rating;

class Member {
private:
    static int nextID;
    int memberID;
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

public:
    Member(string username, string password, string fullname, string phoneNumber, 
           string email, string IDType, string IDNumber, double rating , int ratingCount, int creditPoint);

    static void writeToFile(const string& filePath, const string& content);

    // Method
    string toString() const;
    vector<Member> readData(const string &filename);
    void showInfo() const;
    void updateInfo();
    void topupCredit();
    void createListing(const string& filePath);
    void rateMember(double ratingValue);
    void updateItemInFile(const string& filePath, const Item& updatedItem);
    void updateMemberInFile(const string& filePath);
    void placeBid(Item& item, const string& filePath, const string& membersFilePath);
    void viewAllListings(const string& filePath);
    void searchItems(const string& name, const string& category, int minBid, int maxBid);
    string toLower(const string& str);

    // Getters
    int getMemberID() const;
    string getUsername() const;
    string getPassword() const; 
    string getFullname() const;
    string getPhoneNumber() const;
    string getEmail() const;
    string getIDType() const;
    string getIDNumber() const;
    double getRating() const;
    int getRatingCount() const;
    int getCreditPoints() const;
    vector<Item> getListings() const;

    // Setters
    void setCreditPoints(int creditPoints);
};

#endif
