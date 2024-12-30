#ifndef MEMBER_H
#define MEMBER_H
#include <string>
#include <vector>
#include "User.h"
using namespace std;

class Member : public User {
    private:
        static string member_data;
        string username;
        string email;
        int credit;
        vector<string> listings; // List of item names created by the member
        vector<string> reviews;  // List of reviews received by the member
        vector<string> bids;     // List of bid details placed by the member
    
    public:
        Member();
        Member(string username, string email, int credit);

        // Getters
        string getUsername();
        string getEmail();
        int getCredit();

        // Setters
        void setUsername(string username);
        void setEmail(string email);
        void setCredit(int credit);

        // Methods
        static bool usernameExist(string username);
        void viewAndUpdateInfo(string username, string email);
        void topUpCredit(int amount);
        void addRatingAndReview(string rating, string review);
        void createListing(string itemName);
        vector<string> viewListing();
        void placeBid(string listing, int bidAmount);
        vector<string> searchItems(string keyword, const vector<string>& allListings);
        static Member* getMember(string username);
        static void login(string username, string email);
        static void registerMember(string username, string email, int credit);
        static void readData();
        static void setMemberData(string filePath);q
};
#endif
