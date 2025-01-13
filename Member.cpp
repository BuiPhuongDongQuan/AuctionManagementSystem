#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>
#include <algorithm>
#include <cctype>
#include "Member.h"
#include "Item.h"
#include "Rating.h"
using namespace std;

// Constructor
Member::Member(string username = "", string password = "", string fullname = "", string phoneNumber = "", 
    string email = "", string IDType = "", string IDNumber = "", double rating = 0.0, int ratingCount = 0, int creditPoints = 0)
    : memberID(nextID++) ,username(username), password(password), fullname(fullname), phoneNumber(phoneNumber), email(email),
    IDType(IDType), IDNumber(IDNumber), rating(rating), ratingCount(ratingCount),creditPoints(creditPoints) {}

// Method to write member information to a file
void Member::writeToFile(const string& filePath, const string& content) {
    try {
        // Open file in append mode
        ofstream file(filePath, ios::app);
        if (!file.is_open()) {
            throw ios_base::failure("Failed to open file.");
        }

        // Write content to file
        file << content;

        file.close();
    } catch (const exception& e) {
        throw runtime_error(string("Error writing to file: ") + e.what());
    }
}

string Member::toString() const {
    stringstream ss;
    ss << memberID << "," << username << "," << password << "," << fullname << ","
        << phoneNumber << "," << email << "," << IDType << "," << IDNumber 
        << "," << rating << "," << ratingCount << "," << creditPoints << "\n";
    return ss.str();
}

// Method to read member information from a file
vector<Member> Member::readData(const string& filename) {
    vector<Member> members;
    ifstream inFile(filename);

    if (!inFile) {
        cerr << "Error: Could not open file for reading.\n";
        return members;
    }

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string username, password, fullname, phoneNumber, email, IDType, IDNumber;
        double rating;
        int ratingCount, creditPoints, memberID;

        // Parse the member attributes from the line
        ss >> memberID;
        ss.ignore();
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, fullname, ',');
        getline(ss, phoneNumber, ',');
        getline(ss, email, ',');
        getline(ss, IDType, ',');
        getline(ss, IDNumber, ',');
        ss >> rating;
        ss.ignore();
        ss >> ratingCount;
        ss.ignore();
        ss >> creditPoints;

        // Add the parsed member to the vector
        members.emplace_back(username, password, fullname, phoneNumber, email, IDType, IDNumber, rating, ratingCount, creditPoints);
        members.back().memberID = memberID; // Ensure the member ID is set correctly
    }

    inFile.close();
    return members;
}

// Display item informations
void Member::showInfo() const {
    cout << "========= MEMBER INFORMATION =========\n";
    cout << "Full Name: " << fullname << "\n";
    cout << "Username: " << username << "\n";
    cout << "Email: " << email << "\n";
    cout << "Phone Number: " << phoneNumber << "\n";
    cout << "ID Type: " << IDType << "\n";
    cout << "ID Number: " << IDNumber << "\n";
    cout << "Credit Points: " << creditPoints << "\n";
    cout << "Average Rating: " << rating << " (" << ratingCount << " ratings)\n";
    cout << "======================================\n";
}

// Update member informations
void Member::updateInfo() {
    cout << "========= UPDATE MEMBER INFORMATION =========\n";
    cout << "Select the field you want to update:\n";
    cout << "1. Full Name\n";
    cout << "2. Username\n";
    cout << "3. Password\n";
    cout << "4. Email\n";
    cout << "5. Phone Number\n";
    cout << "6. ID Type\n";
    cout << "7. ID Number\n";
    cout << "8. Exit\n";

    int choice;
    do {
        cout << "Enter your choice (1-8): ";
        cin >> choice;
        cin.ignore(); // Clear input buffer

        switch (choice) {
        case 1:
            cout << "Enter new full name (current: " << fullname << "): ";
            getline(cin, fullname);
            break;
        case 2:
            cout << "Enter new username (current: " << username << "): ";
            getline(cin, username);
            break;
        case 3:
            cout << "Enter new password: ";
            getline(cin, password);
            break;
        case 4:
            cout << "Enter new email (current: " << email << "): ";
            getline(cin, email);
            break;
        case 5:
            cout << "Enter new phone number (current: " << phoneNumber << "): ";
            getline(cin, phoneNumber);
            break;
        case 6:
            cout << "Enter new ID type (current: " << IDType << "): ";
            getline(cin, IDType);
            break;
        case 7:
            cout << "Enter new ID number (current: " << IDNumber << "): ";
            getline(cin, IDNumber);
            break;
        case 8:
            cout << "Exiting update menu.\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
        if (choice >= 1 && choice <= 7) {
            cout << "Field updated successfully.\n";
        }
    } while (choice != 8);

    cout << "=============================================\n";
}

// Topping up credit
void Member::topupCredit() {
    int pointsToTopup;
    char confirmation;

    cout << "Enter the credit points you want to top up: ";
    cin >> pointsToTopup;

    if (pointsToTopup <= 0) {
        cout << "Invalid amount. Please enter a positive number.\n";
        return;
    }

    cout << "You want to top up " << pointsToTopup << " credit points. Confirm? (Y/N): ";
    cin >> confirmation;

    if (confirmation == 'Y' || confirmation == 'y') {
        creditPoints += pointsToTopup;
        cout << "Top-up successful! Your new credit balance is: " << creditPoints << " points.\n";
    } else {
        cout << "Top-up canceled.\n";
    }
}

// Creating Listing Items
void Member::createListing(const string& filePath) {
    string name, category, description;
    int currentBid, bidIncrement;
    int year, month, day, hour, minute, second;

    cout << "===== Create New Listing =====\n";

    // Get item details from the user
    cout << "Enter item name: ";
    getline(cin, name);
    cout << "Enter category: ";
    getline(cin, category);
    cout << "Enter description: ";
    getline(cin, description);
    cout << "Enter starting bid: ";
    cin >> currentBid;
    cout << "Enter bid increment: ";
    cin >> bidIncrement;

    // Get end date and time
    cout << "Enter end date (YYYY MM DD): ";
    cin >> year >> month >> day;
    cout << "Enter end time (HH MM SS): ";
    cin >> hour >> minute >> second;

    // Create the Item
    Item newItem(name, category, description, currentBid, bidIncrement,
                    year, month, day, hour, minute, second);

    // Convert item to string and save it to a file
    try {
        // Use the static method directly
        Item::writeToFile(filePath, newItem.toString());
        cout << "Listing created successfully!\n";
    } catch (const exception& e) {
        cerr << "Error creating listing: " << e.what() << endl;
    }
}

// Method to receive rating from another member
void Member::rateMember(double ratingValue) {
    if (ratingValue < 1 || ratingValue > 5) {
        cout << "Rating must be between 1 and 5.\n";
        return;
    }
    rating = ((rating * ratingCount) + ratingValue) / (++ratingCount);
}   

// Helper function to update the item in the file
void Member::updateItemInFile(const std::string& filePath, const Item& updatedItem) {
    // Read all items from the file
    std::vector<Item> items = Item::readData(filePath);

    // Overwrite the file with updated data
    std::ofstream outFile(filePath, std::ios::trunc); // Truncate mode to overwrite the file
    if (!outFile.is_open()) {
        throw std::runtime_error("Error: Could not open file for writing.");
    }

    for (const auto& item : items) {
        if (item.getName() == updatedItem.getName()) {
            // Write the updated item to the file
            outFile << updatedItem.toString();
        } else {
            // Write the original item to the file
            outFile << item.toString();
        }
    }

    outFile.close();
}

// Helper function to update the member in the file
void Member::updateMemberInFile(const std::string& filePath) {
    // Read all members from the file
    std::vector<Member> members = Member::readData(filePath);

    // Overwrite the file with updated data
    std::ofstream outFile(filePath, std::ios::trunc); // Truncate mode to overwrite the file
    if (!outFile.is_open()) {
        throw std::runtime_error("Error: Could not open file for writing.");
    }

    for (const auto& member : members) {
        if (member.getMemberID() == this->getMemberID()) {
            // Write the updated member to the file
            outFile << toString();
        } else {
            // Write the original member to the file
            outFile << member.toString();   
        }
    }

    outFile.close();
}

// Method to place bid
void Member::placeBid(Item& item, const std::string& filePath, const std::string& membersFilePath) {
    while (true) {
        cout << "\n========= Place a Bid =========\n";
        cout << "Your current credit points: " << creditPoints << "\n";
        cout << "Current highest bid: $" << item.getCurrentBid() << "\n";
        cout << "Minimum bid increment: $" << item.getBidIncrement() << "\n";

        // Calculate the minimum bid amount
        int minBid = item.getCurrentBid() + item.getBidIncrement();

        cout << "Enter your bid (minimum $" << minBid << "): ";
        int bid;
        cin >> bid;

        // Input validation
        if (cin.fail() || bid < minBid) {
            cout << "Invalid bid! Your bid must be at least $" << minBid << ". Try again.\n";
            cin.clear(); // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
            continue;
        }

        // Check if the user has enough credit points
        if (bid - item.getCurrentBid() > creditPoints) {
            cout << "Insufficient credit points! You only have $" << creditPoints << ".\n";
            cout << "Please add more credits or lower your bid.\n";
            continue;
        }

        // Deduct bid amount from user's credit points
        creditPoints -= bid - item.getCurrentBid();

        // Update the item's current bid to the new bid
        setCreditPoints(creditPoints);
        item.setCurrentBid(bid);

        // Update the item in the file
        updateItemInFile(filePath, item);

        // Update the member's data in the members file
        updateMemberInFile(membersFilePath);

        cout << "Congratulations! You are now the highest bidder with a bid of $" << bid << ".\n";

        if(creditPoints <= 0) {
            cout << "You are out of Credit Point! Please add more credits"; 
            break;
        }

        // Ask the user if they want to place another bid
        char choice;
        cout << "Do you want to place another bid? (y/n): ";
        cin >> choice;

        if (choice == 'n' || choice == 'N') {
            cout << "Thank you for bidding. Good luck!\n";
            break;
        }
    }
}

// View all item listings in items.txt
void Member::viewAllListings(const string& filePath) {
    // Read all items from the file
    vector<Item> items = Item::readData(filePath);

    if (items.empty()) {
        cout << "No items listed currently.\n";
        return;
    }

    cout << "========= All Item Listings =========\n";
    for (const auto& item : items) {
        cout << "Item Name: " << item.getName() << "\n";
        cout << "Category: " << item.getCategory() << "\n";
        cout << "Description: " << item.getDescription() << "\n";
        cout << "Current Bid: $" << item.getCurrentBid() << "\n";
        cout << "Bid Increment: $" << item.getBidIncrement() << "\n";
        cout << "End Date and Time: " << item.getShowTime() << "\n";
        cout << "=====================================\n";
    }
}

// Utility function to convert strings to lowercase for case-insensitive comparison
string Member::toLower(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

// Method to search items based on name, category, or credit point range
void Member::searchItems(const string& name, const string& category, int minBid, int maxBid) {
    vector<Item> results;
    vector<Item> listings = Item::readData("item.txt"); // This should contain the actual list of items to search from

    for (const auto& item : listings) {
        bool matchName = name.empty() || toLower(item.getName()).find(toLower(name)) != string::npos;
        bool matchCategory = category.empty() || toLower(item.getCategory()).find(toLower(category)) != string::npos;
        bool matchBidRange = (minBid == -1 || item.getCurrentBid() >= minBid) &&
                              (maxBid == -1 || item.getCurrentBid() <= maxBid);

        if (matchName && matchCategory && matchBidRange) {
            results.push_back(item);
        }
    }

    // If no results, notify the user
    if (results.empty()) {
        cout << "No items found matching the criteria.\n";
    } else {
        cout << "========= Search Results =========\n";
        for (const auto& item : results) {
            cout << "Item Name: " << item.getName() << "\n";
            cout << "Category: " << item.getCategory() << "\n";
            cout << "Description: " << item.getDescription() << "\n";
            cout << "Current Bid: $" << item.getCurrentBid() << "\n";
            cout << "Bid Increment: $" << item.getBidIncrement() << "\n";
            cout << "End Date and Time: " << item.getShowTime() << "\n";
            cout << "=====================================\n";
        }
    }
}


// Getter 
int Member::getMemberID() const { return memberID; }
string Member::getUsername() const { return username; }
string Member::getPassword() const { return password; }
string Member::getFullname() const { return fullname; }
string Member::getPhoneNumber() const { return phoneNumber; }
string Member::getEmail() const { return email; }
string Member::getIDType() const { return IDType; }
string Member::getIDNumber() const { return IDNumber; }
double Member::getRating() const { return rating; }
int Member::getRatingCount() const { return ratingCount; }
int Member::getCreditPoints() const { return creditPoints; }
vector<Item> Member::getListings() const { return listings; }

// Setter
void Member::setCreditPoints(int creditPoints) {
    this -> creditPoints = creditPoints;
}


int Member::nextID = 1;
