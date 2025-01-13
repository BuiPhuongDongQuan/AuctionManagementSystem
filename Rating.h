#ifndef RATING_H
#define RATING_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

class Member;

class Item;

class Rating {
private:
    Member* buyer;
    Member* seller;
    double buyerRating;
    double sellerRating;

public:
    Rating(Member* buyer, Member* seller);

    void sellerRatesBuyer(double rating);

    void buyerRatesSeller(double rating);

    void showRatings() const;  

    // Getter
    double getBuyerRating() const;
    double getSellerRating() const;
};

#endif