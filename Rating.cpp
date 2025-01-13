#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "Rating.h"
#include "Member.h"
using namespace std;

Rating::Rating(Member* buyer, Member* seller)
    : buyer(buyer), seller(seller), buyerRating(0), sellerRating(0) {}

// Seller rates the buyer
void Rating::sellerRatesBuyer(double rating) {
    if (buyer) {
        buyer->rateMember(rating);
        buyerRating = rating;
    } else {
        cout << "Buyer information is missing." << endl;
    }
}

// Buyer rates the seller
void Rating::buyerRatesSeller(double rating) {
    if (seller) {
        seller->rateMember(rating);
        sellerRating = rating;
    } else {
        cout << "Seller information is missing." << endl;
    }
}

// Display ratings for the transaction
void Rating::showRatings() const {
    if (buyer && seller) {
        cout << "Transaction complete between " << seller->getUsername()
             << " (Seller) and " << buyer->getUsername() << " (Buyer).\n";
        cout << seller->getUsername() << " rated " << buyer->getUsername() << ": " << buyerRating << "\n";
        cout << buyer->getUsername() << " rated " << seller->getUsername() << ": " << sellerRating << "\n";
    } else {
        cout << "Transaction information is incomplete." << endl;
    }
}   

//Getter
double Rating::getBuyerRating() const { return buyerRating; }
double Rating::getSellerRating() const { return sellerRating; } 