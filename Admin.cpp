#include "Admin.h"
#include "functions/Function.h"
#include <iostream>
#include <fstream>
using namespace std;

// Admin::Admin() : User(){}
// Admin::Admin(string username, string password, string fullname, string phoneNumber, string email, string IDType, string IDNumber, int creditPoints) : User(username, password, fullname, phoneNumber, email, IDType, IDNumber, creditPoints){}

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


        while (getline(file, line)) {

            istringstream iss(line);
            string ID,username, password, fullName, phoneNumber, email, idType, idNumber, ratingCount, rating, creditPoints;

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
                getline(iss, ratingCount, ',') &&
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
                     << setw(15) << ratingCount
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

void Admin::viewItemData(string filePath){
    try {
        ifstream file(filePath);
        if (!file.is_open()) {
            throw ios_base::failure("Fail to open file.");
        }

        // Print table header
        cout << left << setw(15) << "Name"
             << setw(20) << "Category"
             << setw(20) << "Description"
             << setw(20) << "Starting Bid $"
             << setw(20) << "Current Bid $"
             << setw(20) << "Increment Bid $"
             << setw(20) << "Expiry Date"
             << endl;

        cout << string(140, '-') << endl; // Divider line for the table

        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string name, category, description, expiryDate;
            int startingBid, currentBid, bidIncrement;

            // Parse line (comma-separated values)
            if (getline(iss, name, ',') &&
                getline(iss, category, ',') &&
                getline(iss, description, ',') &&
                (iss >> startingBid).ignore() &&
                (iss >> currentBid).ignore() &&
                (iss >> bidIncrement).ignore() &&
                getline(iss, expiryDate)) {

                // Print parsed data in formatted columns
                cout << left << setw(15) << name
                     << setw(20) << category
                     << setw(20) << description
                     << setw(20) << startingBid
                     << setw(20) << currentBid
                     << setw(20) << bidIncrement
                     << setw(20) << expiryDate
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

