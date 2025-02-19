#include "Admin.h"
#include "functions/Function.h"
#include <iostream>
#include <fstream>
using namespace std;

// Admin::Admin() : User(){}
// Admin::Admin(string username, string password, string fullname, string phoneNumber, string email, string IDType, string IDNumber, int creditPoints) 
//: User(username, password, fullname, phoneNumber, email, IDType, IDNumber, creditPoints){}

void Admin::viewMemberInfo(string filePath){
    try {
        ifstream file(filePath);
        if (!file.is_open()) {
            throw ios_base::failure("Fail to open file.");
        }

        // Print table header
        cout << left << setw(5) << "ID"
             << setw(15) << "Username"
             << setw(15) << "Password"
             << setw(15) << "Full Name"
             << setw(15) << "Phone Number"
             << setw(20) << "Email"
             << setw(15) << "ID Type"
             << setw(15) << "ID Number"
             << setw(15) << "Rating"
             << setw(15) << "Rated Times"
             << setw(15) << "Credit Points"
             << endl;

        cout << string(160, '-') << endl; // Divider line for the table

        string line;
        bool isHeader = true;

        while (getline(file, line)) {
            // Skip the header row
            if (isHeader) {
                isHeader = false;
                continue;
            }

            // Skip blank lines
            if (line.empty()) {
                continue;
            }

            istringstream iss(line);
            string ID,username, password, fullName, phoneNumber, email, idType, idNumber, ratedTimes, rating, creditPoints;

            // Parse line (comma-separated values)
            if (getline(iss, ID, ',') &&
                getline(iss, username, ',') &&
                getline(iss, password, ',') &&
                getline(iss, fullName, ',') &&
                getline(iss, phoneNumber, ',') &&
                getline(iss, email, ',') &&
                getline(iss, idType, ',') &&
                getline(iss, idNumber, ',') &&
                getline(iss, rating, ',') &&
                getline(iss, ratedTimes, ',') &&
                getline(iss, creditPoints)) {

                // Print parsed data in formatted columns
                cout << left << setw(5) << ID
                     << setw(15) << username
                     << setw(15) << password
                     << setw(15) << fullName
                     << setw(15) << phoneNumber
                     << setw(20) << email
                     << setw(15) << idType
                     << setw(15) << idNumber
                     << setw(15) << rating
                     << setw(15) << ratedTimes
                     << setw(15) << creditPoints
                     << endl;
            } else {
                cerr << "Error: Malformed line -> " << line << endl;
            }
        }

        file.close();
    } catch (const ios_base::failure& e) {
        cerr << "An error occurred: " << e.what() << endl;
    }
}

void Admin::viewItemData(string filePath) {
    try {
        ifstream file(filePath);
        if (!file.is_open()) {
            throw ios_base::failure("Failed to open file.");
        }

        // Print table header
        cout << left << setw(5) << "ID"
             << setw(10) << "SellerID"
             << setw(15) << "Name"
             << setw(15) << "Category"
             << setw(20) << "Description"
             << setw(15) << "Starting Bid"
             << setw(15) << "Current Bid"
             << setw(15) << "Increment Bid"
             << setw(15) << "Rating Points"
             << setw(20) << "Expiry Date"
             << setw(20) << "Expiry Time"
             << endl;

        cout << string(160, '-') << endl; // Divider line for the table

        string line;
        bool isHeader = true;

        while (getline(file, line)) {
            // Skip the header row
            if (isHeader) {
                isHeader = false;
                continue;
            }

            // Skip blank lines
            if (line.empty()) {
                continue;
            }
            istringstream iss(line);
            string ID, sellerID, name, category, description, expiryDate, expiryTime;
            int startingBid, currentBid, bidIncrement;
            double ratingPoints;

            // Ensure the CSV data is correctly split
            if (getline(iss, ID, ',') &&
                getline(iss, sellerID, ',') &&
                getline(iss, name, ',') &&
                getline(iss, category, ',') &&
                getline(iss, description, ',') &&
                (iss >> startingBid).ignore() &&
                (iss >> currentBid).ignore() &&
                (iss >> bidIncrement).ignore() &&
                (iss >> ratingPoints).ignore() &&
                getline(iss, expiryDate, ',') &&
                getline(iss, expiryTime)) {
                
                // Print parsed data in formatted columns
                cout << left << setw(5) << ID
                     << setw(10) << sellerID
                     << setw(15) << name
                     << setw(15) << category
                     << setw(20) << description
                     << setw(15) << startingBid
                     << setw(15) << currentBid
                     << setw(15) << bidIncrement
                     << setw(15) << ratingPoints
                     << setw(20) << expiryDate
                     << setw(20) << expiryTime
                     << endl;
            } else {
                cerr << "Error: Malformed line -> " << line << endl;
            }
        }

        file.close();
    } catch (const ios_base::failure& e) {
        cerr << "An error occurred: " << e.what() << endl;
    }
}