#include "Member.h"
#include <iostream>
using namespace std;

// Static member initialization
string Member::member_data;

// Constructor definitions
Member::Member() : username(""), email(""), credit(0) {}

Member::Member(string username, string email, int credit)
    : username(username), email(email), credit(credit) {}

// Getters
string Member::getUsername() { return username; }

string Member::getEmail() { return email; }

int Member::getCredit() { return credit; }

// Setters
void Member::setUsername(string username) { this->username = username; }

void Member::setEmail(string email) { this->email = email; }

void Member::setCredit(int credit) { this->credit = credit; }

// Methods
bool Member::usernameExist(string username) {
    // Example implementation
    return false;
}

void Member::viewAndUpdateInfo(string username, string email) {
    this->username = username;
    this->email = email;
}

void Member::topUpCredit(int amount) {
    if (amount <= 0) {
        cout << "Top-up amount must be greater than zero.\n";
        return;
    }
    credit += amount;
}

void Member::addRatingAndReview(string rating, string review) {
    reviews.push_back("Rating: " + rating + ", Review: " + review);
}

void Member::createListing(string itemName) {
    listings.push_back(itemName);
}

vector<string> Member::viewListing() { return listings; }

void Member::placeBid(string listing, int bidAmount) {
    if (bidAmount > credit) {
        cout << "Insufficient credit to place bid.\n";
        return;
    }
    bids.push_back("Bid on " + listing + ": " + to_string(bidAmount));
    credit -= bidAmount;
}

vector<string> Member::searchItems(string keyword, const vector<string>& allListings) {
    vector<string> results;
    for (const auto& item : allListings) {
        if (item.find(keyword) != string::npos) {
            results.push_back(item);
        }
    }
    return results;
}

Member* Member::getMember(string username) {
    // Example implementation
    return nullptr;
}

void Member::login(string username, string email) {
    cout << "Login successful for: " << username << endl;
}

void Member::registerMember(string username, string email, int credit) {
    cout << "Registered member: " << username << endl;
}

void Member::readData() {
    // Example implementation
}

void Member::setMemberData(string filePath) {
    member_data = filePath;
}
