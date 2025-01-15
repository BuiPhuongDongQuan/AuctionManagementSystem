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
        cout << left << setw(20) << "Username"
             << setw(20) << "Password"
             << setw(20) << "Full Name"
             << setw(20) << "Phone Number"
             << setw(20) << "Email"
             << setw(20) << "ID Type"
             << setw(20) << "ID Number"
             << setw(20) << "Credit Points"
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
            string username, password, fullName, phoneNumber, email, idType, idNumber;
            int creditPoints;

            // Parse line (comma-separated values)
            if (getline(iss, username, ',') &&
                getline(iss, password, ',') &&
                getline(iss, fullName, ',') &&
                getline(iss, phoneNumber, ',') &&
                getline(iss, email, ',') &&
                getline(iss, idType, ',') &&
                getline(iss, idNumber, ',') &&
                (iss >> creditPoints)) {

                // Print parsed data in formatted columns
                cout << left << setw(20) << username
                     << setw(20) << password
                     << setw(20) << fullName
                     << setw(20) << phoneNumber
                     << setw(20) << email
                     << setw(20) << idType
                     << setw(20) << idNumber
                     << setw(20) << creditPoints
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
             << setw(15) << "Category"
             << setw(20) << "Description"
             << setw(10) << "Stock"
             << setw(10) << "Sold"
             << setw(10) << "Discount"
             << setw(20) << "Expiry Date"
             << endl;

        cout << string(90, '-') << endl; // Divider line for the table

        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string name, category, description, expiryDate;
            int stock, sold, discount;

            // Parse line (comma-separated values)
            if (getline(iss, name, ',') &&
                getline(iss, category, ',') &&
                getline(iss, description, ',') &&
                (iss >> stock).ignore() &&
                (iss >> sold).ignore() &&
                (iss >> discount).ignore() &&
                getline(iss, expiryDate)) {

                // Print parsed data in formatted columns
                cout << left << setw(15) << name
                     << setw(15) << category
                     << setw(20) << description
                     << setw(10) << stock
                     << setw(10) << sold
                     << setw(10) << discount
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

