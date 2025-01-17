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
#include "Bid.h"
#include "Menu.h"
#include "functions/Function.h"
using namespace std;

// Constructor
Member::Member() : User(){}
Member::Member(string memberID = "", string username = "", string password = "", string fullname = "", string phoneNumber = "", 
    string email = "", string IDType = "", string IDNumber = "", double rating = 0.0, int ratingCount = 0, int creditPoints = 0)
    : User(memberID ,username, password, fullname, phoneNumber, email,
    IDType, IDNumber, rating, ratingCount,creditPoints) {}

// Login function
void Member::login(string username, string password){
    readData();
    User* member = getUser(username);
    if(member == nullptr){
        cout << "Username not found. Please register to begin." << endl;
    }else{
        // Authenticate the user
        if(member->authentication(username, password)){
            cout << "Welcome back " << username << endl;
            setUsername(username);
            Menu::memberDashboard();
        }else{
            cout << "Login failed! Username or password is incorrect." << endl;
            Menu::loginMenu();
        }
    }
}

void Member::showInfo(string username){
    User::readData();
    for(User member : users){
        if(member.getUsername() == username){
            cout << "========= MEMBER INFORMATION =========\n";
            cout << "Full Name: " << member.getFullname() << "\n";
            cout << "Username: " << member.getUsername() << "\n";
            cout << "Email: " << member.getEmail() << "\n";
            cout << "Phone Number: " << member.getPhoneNumber() << "\n";
            cout << "ID Type: " << member.getIDType() << "\n";
            cout << "ID Number: " << member.getIDNumber() << "\n";
            cout << "Credit Points: " << member.getCreditPoints() << "\n";
            cout << "Average Rating: " << member.getRating() << " (" << member.getRatedTimes() << " ratings)\n";
            cout << "======================================\n";
        }
    }
}

// Update member informations
void Member::updateInfo(int userInput, string username) {
    User* member = getUser(username);
    if(member->getUserID().empty()){
        cerr << "Error: User not found." << std::endl;
        return;
    }
    // Extract old content
    std::string oldInfo = member->getUserID() + "," + member->getUsername() + "," + member->getPassword() + "," +
                          member->getFullname() + "," + member->getPhoneNumber() + "," + member->getEmail() + "," +
                          member->getIDType() + "," + member->getIDNumber() + "," + to_string(member->getRating()) + "," +
                          to_string(member->getRatedTimes()) + "," + to_string(member->getCreditPoints());

    vector<string> updateMemberInfo = Function::split(oldInfo, ',');
    string updatedInfo;
    string newInfo;
        switch (userInput) {
        case 1:
            cout << "Enter new full name: ";
            getline(cin, newInfo);
            updateMemberInfo[3] = newInfo;
            updatedInfo = Function::vectorToCSVString(updateMemberInfo);
            Function::modifyFile("members.txt", oldInfo, updatedInfo);
            break;
        case 2:
            cout << "Enter new username: ";
            getline(cin, newInfo);
            updateMemberInfo[1] = newInfo;
            updatedInfo = Function::vectorToCSVString(updateMemberInfo);
            Function::modifyFile("members.txt", oldInfo, updatedInfo);
            break;
        case 3:
            cout << "Enter new password: ";
            getline(cin, newInfo);
            updateMemberInfo[2] = newInfo;
            updatedInfo = Function::vectorToCSVString(updateMemberInfo);
            Function::modifyFile("members.txt", oldInfo, updatedInfo);
            break;
        case 4:
            cout << "Enter new email: ";
            getline(cin, newInfo);
            updateMemberInfo[5] = newInfo;
            updatedInfo = Function::vectorToCSVString(updateMemberInfo);
            Function::modifyFile("members.txt", oldInfo, updatedInfo);
            break;
        case 5:
            cout << "Enter new phone number: ";
            getline(cin, newInfo);
            updateMemberInfo[4] = newInfo;
            updatedInfo = Function::vectorToCSVString(updateMemberInfo);
            Function::modifyFile("members.txt", oldInfo, updatedInfo);
            break;
        case 6:
            cout << "Enter new ID type: ";
            getline(cin, newInfo);
            updateMemberInfo[6] = newInfo;
            updatedInfo = Function::vectorToCSVString(updateMemberInfo);
            Function::modifyFile("members.txt", oldInfo, updatedInfo);
            break;
        case 7:
            cout << "Enter new ID number: ";
            getline(cin, newInfo);
            updateMemberInfo[7] = newInfo;
            updatedInfo = Function::vectorToCSVString(updateMemberInfo);
            Function::modifyFile("members.txt", oldInfo, updatedInfo);
            break;
        case 8:
            cout << "Exiting update menu.\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    cout << "=============================================\n";

}

// Topping up credit
void Member::topupCredit(string username) {
    User* member = getUser(username);
    if(member->getUserID().empty()){
        cerr << "Error: User not found." << std::endl;
        return;
    }
    // Extract old content
    std::string oldInfo = member->getUserID() + "," + member->getUsername() + "," + member->getPassword() + "," +
                          member->getFullname() + "," + member->getPhoneNumber() + "," + member->getEmail() + "," +
                          member->getIDType() + "," + member->getIDNumber() + "," + to_string(member->getRating()) + "," +
                          to_string(member->getRatedTimes()) + "," + to_string(member->getCreditPoints());

    vector<string> updateMemberInfo = Function::split(oldInfo, ',');
    string updatedInfo;
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
    cin.ignore();

    if (confirmation == 'Y' || confirmation == 'y') {
        // Get the current credit points
        int currentCreditPoints = member->getCreditPoints();

        // Add the top-up points
        int newCreditPoints = currentCreditPoints + pointsToTopup;

        // Update the credit points in the vector
        updateMemberInfo[10] = to_string(newCreditPoints);

        // Convert the updated information back to a CSV format string
        updatedInfo = Function::vectorToCSVString(updateMemberInfo);

        // Modify the file
        Function::modifyFile("members.txt", oldInfo, updatedInfo);

        // Update the user's credit points locally
        member->setCreditPoints(newCreditPoints);

    } else {
        cout << "Top-up canceled.\n";
    }
}

// Creating Listing Items
void Member::createListing(string username) {
    User* member = getUser(username);
    string name, category, description, itemID;
    int startingBid, currentBid, bidIncrement;
    double ratePoint;
    int year, month, day, hour, minute, second;
    int countLine = Function::countLine("item.txt");

    cout << "===== Create New Listing =====\n";
    // Create unique ID
    string id = "I" + to_string(countLine);
    // Get item details from the user
    cout << "Enter item name: ";
    getline(cin, name);
    cin.ignore(); // Clear leftover newline from input buffer

    cout << "Enter category: ";
    getline(cin, category);

    cout << "Enter description: ";
    getline(cin, description);

    cout << "Enter starting bid: ";
    cin >> startingBid;
    currentBid = startingBid;

    cout << "Enter bid increment: ";
    cin >> bidIncrement;

    cout << "Enter the minimum rating required to view this item (ratePoint, 0-5): ";
    cin >> ratePoint;
    if (ratePoint < 0 || ratePoint > 5) {
        cerr << "Invalid ratePoint value. Setting to default (0.0).\n";
        ratePoint = 0.0;
    }

    // Clear the buffer before getting the next set of inputs
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Get end date and time
    cout << "Enter end date (YYYY MM DD): ";
    cin >> year >> month >> day;

    cout << "Enter end time (HH MM SS): ";
    cin >> hour >> minute >> second;

    // Create the Item
    string newItem = "\n" + id + "," + member->getUserID() + "," + name + "," + category + "," + description + "," + to_string(startingBid) + "," + 
    to_string(currentBid) + "," + to_string(bidIncrement) + "," + to_string(ratePoint) + "," + to_string(year) + "/" + to_string(month) + "/" + to_string(day) + "," + to_string(hour) + ":" + to_string(minute) + ":" + to_string(second);

    // Convert item to string and save it to a file
    Function::writeToFile("item.txt", newItem);
    cout << "Listing created successfully!\n";
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
    Item::readItemData();
    const auto& items = Item::getItems();

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
    User::readData();

    // Overwrite the file with updated data
    std::ofstream outFile(filePath, std::ios::trunc); // Truncate mode to overwrite the file
    if (!outFile.is_open()) {
        throw std::runtime_error("Error: Could not open file for writing.");
    }

    for (const auto& member : users) {
        if (member.getUserID() == this->getUserID()) {
            // Write the updated member to the file
            outFile << toString();
        } else {
            // Write the original member to the file
            outFile << member.toString();   
        }
    }

    outFile.close();
}

// Helper function to update credit points in the file based on memberID
void Member::updateMemberCreditPointsInFile(const string& filePath) {
    // Read all members from the file
    vector<Member> members = Member::readData(filePath);

    // Open the file to overwrite with updated credit points
    ofstream outFile(filePath, ios::trunc); // Truncate mode to overwrite
    if (!outFile.is_open()) {
        throw runtime_error("Error: Could not open file for writing.");
    }

    for (auto& member : members) {
        if (member.getMemberID() == this->getMemberID()) {
            // Update the member's credit points in the file
            member.setCreditPoints(creditPoints); // Assuming a setCreditPoints function exists
            outFile << member.toString();
        } else {
            // Write other members without modification
            outFile << member.toString();
        }
    }

    outFile.close();
    cout << "Credit points updated successfully in the file.\n";
}

void Member::placeBid(string& auctionID, int memberID, int bidAmount, unordered_map<string, int>& previousBids, int currentBid, const string& filePath) {
    const string fileMemberPath = "bids.txt";
    Bid bidInstance;
    string memberIDStr = to_string(memberID);

    // Calculate the total required credit points for active bids
    int totalActiveBidCredits = 0;
    for (const auto& bid : activeBids) {
        totalActiveBidCredits += bid.getActiveBid();
    }

    // Get the previous bid amount for this auction
    int previousBidAmount = previousBids[auctionID];

    // Calculate the incremental credit requirement for the new bid
    int additionalCreditsRequired = bidAmount - previousBidAmount;

    // Check if the member has enough credit points to place the new bid
    if ((creditPoints - totalActiveBidCredits) < additionalCreditsRequired) {
        cout << "Insufficient credit points to place this bid. Current available credits: " 
             << (creditPoints - totalActiveBidCredits) << ". Required: " << additionalCreditsRequired << "\n";
        return;
    }

    // Place or update the bid
    if (previousBidAmount > 0) {
        // Update the existing bid
        creditPoints -= additionalCreditsRequired;
        previousBids[auctionID] = bidAmount;
        cout << "Bid updated from " << previousBidAmount << " to " << bidAmount << " successfully!\n";
    } else {
        // Place a new bid
        creditPoints -= bidAmount;
        previousBids[auctionID] = bidAmount;
        cout << "New bid of " << bidAmount << " placed successfully!\n";
    }

    // Check if the bid is already active for this auction and member
    bool isActive = bidInstance.isActiveBid(auctionID, memberID, fileMemberPath);
    if (isActive) {
        // Update the bid if it already exists
        int previousBid = previousBids[auctionID];
        int bidDifference = bidAmount - previousBid;
                
        if (bidDifference > (creditPoints - totalActiveBidCredits)) {
            cout << "Insufficient credit points to increase the bid by " << bidDifference << ".\n";
            return;
        }

        // Adjust the credit points for the difference
        creditPoints -= bidDifference;
        previousBids[auctionID] = bidAmount;

        // Update the bid in the system
        Bid updatedBid(auctionID, memberID, bidAmount, true);
        try {
            Function::writeToFile(fileMemberPath, updatedBid.toString());
            cout << "Bid updated successfully!\n";
        } catch (const exception& e) {
            cerr << "Error updating bid: " << e.what() << endl;
        }
    } else {
        // Place a new bid
        if (bidAmount > (creditPoints - totalActiveBidCredits)) {
            cout << "Insufficient credit points to place the bid.\n";
            return;
        }

        Bid newBid(auctionID, memberID, bidAmount, true);
        try {
            Function::writeToFile(fileMemberPath, newBid.toString());
            cout << "New bid placed successfully!\n";
        } catch (const exception& e) {
            cerr << "Error placing new bid: " << e.what() << endl;
        }

        // Deduct the bid amount from credit points
        creditPoints -= bidAmount;
        previousBids[auctionID] = bidAmount;
        activeBids.emplace_back(newBid);
    }
    updateMemberCreditPointsInFile(filePath);
}

// View all item listings in items.txt
void Member::viewListings(const string& filePath) {
    // Read all items from the file
    Item::readItemData();
    const auto& items = Item::getItems();

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

void Member::finalizeBid(const string& auctionID, bool won) {
    auto it = find_if(activeBids.begin(), activeBids.end(), [&auctionID](const Bid& bid) {
        return bid.getAuctionID() == auctionID;
    });

    if (it != activeBids.end()) {
        if (won) {
            cout << "You have won the auction for " << auctionID << ". Credit points have been officially deducted.\n";
        } else {
            // Refund the credit points for the unsuccessful bid
            creditPoints += it->getActiveBid();
            cout << "You did not win the auction for " << auctionID << ". Your credit points have been refunded.\n";
        }

        // Remove the bid from active bids
        activeBids.erase(it);
        updateMemberCreditPointsInFile("members.txt");
    } else {
        cerr << "No active bid found for auction " << auctionID << ".\n";
    }
}

// Getter 
vector<Item> Member::getListings() const { return listings; }
