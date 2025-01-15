#include "Guest.h"
#include "Item.h"
#include <iostream>
#include <fstream>
using namespace std;

Guest::Guest() : User() {}

void Guest::viewItem(string filePath){
    try {
        ifstream file(filePath);
        if (!file.is_open()) {
            throw ios_base::failure("Fail to open file.");
        }

        // Print table header
        cout << left << setw(15) << "Name"
             << setw(20) << "Category"
             << setw(20) << "Description"
             << endl;

        cout << string(50, '-') << endl; // Divider line for the table

        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string name, category, description;

            // Parse line (comma-separated values)
            if (getline(iss, name, ',') &&
                getline(iss, category, ',') &&
                getline(iss, description, ',')) {

                // Print parsed data in formatted columns
                cout << left << setw(15) << name
                     << setw(20) << category
                     << setw(20) << description
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