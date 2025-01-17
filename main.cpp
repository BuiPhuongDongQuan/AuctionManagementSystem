// ! Test Item Function
#include <iostream>
#include <unordered_map>
#include <vector>
#include "Member.h"
#include "Item.h"
#include "Auction.h"
#include "Item.h"
#include "Rating.h"
#include "Bid.h"
#include "functions/Function.h"
#include <fstream>

using namespace std;

// int main() {
//     // Set item data file
//     const string filePath = "item.txt";
//     Item::setItemData(filePath);

//     // Test constructor and display details
//     Item item(1, "Laptop", "Electronics", "A high-end gaming laptop", 
//                1000, 1000, 50, 4.5, 2025, 1, 15, 12, 0, 0);
//     Item item2(2, "Smartphone", "Electronics", "A flagship smartphone", 
//                800, 800, 25, 3.0, 2025, 2, 1, 10, 30, 0);

//     // Test toString()
//     cout << "\nTesting toString()\n";
//     cout << "Item as string: " << item.toString();
//     cout << "Item as string: " << item2.toString();

//     // Test writeToFile()
//     cout << "\nTesting writeToFile()\n";
//     Item::writeToFile(filePath, item.toString());
//     Item::writeToFile(filePath, item2.toString());

//     // Simulate a buyer with rating 3.5
//     double buyerRating = 3.5;
//     cout << "Items visible to buyer with rating " << buyerRating << ":\n";
//     vector<Item> visibleItems = Item::getVisibleItems(buyerRating);
//     Item::displayItems(visibleItems);

    // Test readItemData()
    //cout << "\nTesting readItemData()\n";
    //Item::readItemData();
    //const vector<Item>& items = Item::getItems();
    //for (const auto& i : items) {
        //i.displayLimitedDetails();
    //}

    // Test addListing()
    //cout << "\nTesting addListing()\n";
    //item.addListing();

    // Test removeListing()
    //cout << "\nTesting removeListing()\n";
    //if (!item.removeListing()) {
        //cout << "Failed to remove listing.\n";
    //}

    // Test isTimerDone()
    //cout << "\nTesting isTimerDone()\n";
    //if (item.isTimerDone()) {
    //cout << "Timer is done for the item.\n";
    //} else {
        //cout << "Timer is still running for the item.\n";
    //}

    // Test startTimer() (commented to avoid long wait in tests)
    //cout << "\nTesting startTimer()\n";
    //item.startTimer();

    // Test removeFromFile()
    //cout << "\nTesting removeFromFile()\n";
    //Item::removeFromFile(filePath, "Laptop");
    //Item::readItemData();
    //for (const auto& i : Item::getItems()) {
        //i.displayLimitedDetails();
    //}

    // Cleanup
    // cout << "\nCleaning up test file\n";
    // remove(filePath.c_str());

    //cout << "\nAll tests completed.\n";
//     return 0;
// }

// ! Test Member Function
// #include <iostream>
// #include <vector>
// #include "Member.h"
// #include "Item.h"
// #include "Auction.h"
// #include "Item.h"
// #include "Rating.h"
// #include "functions/Function.h"


// using namespace std;

// int main()
// {
//     // File paths
//     const string membersFile = "members.txt";
//     const string itemsFile = "item.txt";

//     // Create a Member
//     Member member4("user1", "pass123", "John Doe", "1234567890", "john@example.com", "IDCard", "A12345678", 4.5, 10, 100);
//     Function::writeToFile(membersFile, member4.toString());
//     cout << "Member created and saved to file.\n";

//     // Display member information
//     cout << "Displaying member information:\n";
//     member4.showInfo();

//     // Update member information
//     cout << "\nUpdating member information:\n";
//     member4.updateInfo(membersFile);
//     member4.showInfo();

//     // Top up credits
//     cout << "\nTopping up credit points:\n";
//     member4.topupCredit(membersFile);
//     member4.showInfo();

//     // Create a listing
//     cout << "\nCreating a listing:\n";
//     member4.createListing(itemsFile);

//     // View all listings
//     cout << "\nViewing all listings:\n";
//     member4.viewAllListings(itemsFile);

//     // Search for items
//     cout << "\nSearching for items:\n";
//     member4.searchItems("Iphone15", "Electronic", -1, -1);

//     // Place a bid on an item
//     vector<Item> items = Item::readData(itemsFile);
//     if (!items.empty())
//     {
//         cout << "\nPlacing a bid on the first item:\n";
//         member4.placeBid(items[0], itemsFile, membersFile);
//     }
//     else
//     {
//         cout << "No items available for bidding.\n";
//     }

//         // Simulate reading items from file
//     items = Item::readData(itemsFile);
//     if (!items.empty()) {
//         cout << "\n=== Update Current Bid by Item ID ===\n";

//         // Display the first item
//         const string itemID = items[0].getItemID();
//         cout << "Original bid for item ID " << itemID << ": $" << items[0].getCurrentBid() << endl;

//         // Update the current bid
//         bool updated = Item::updateCurrentBidByID(itemID, 1500);

//         if (updated) {
//             cout << "New bid for item ID " << itemID << ": $" << items[0].getCurrentBid() << endl;
//         } else {
//             cout << "Failed to update the bid.\n";
//         }
//     } else {
//         cout << "No items available for updating bids.\n";
//     }

//     // Rate the member
//     cout << "\nRating the member:\n";
//     member4.rateMember(5.0);
//     member4.showInfo();

//     // Update the member in the file
//     member4.updateMemberInFile(membersFile);

//     // --- Auction Testing Starts Here ---
//     if (!items.empty())
//     {
//         cout << "\n=== Auction Testing ===\n";

//         // Create an auction for the first item
//         Auction auction(items[0]);

//         // Start the auction
//         auction.startAuction();

//         // Create test members for bidding
//         Member buyer1("buyer1", "pass123", "Buyer One", "1234567890", "buyer1@example.com", "ID", "B123", 4.7, 5, 1000);
//         Member buyer2("buyer2", "pass123", "Buyer Two", "1234567891", "buyer2@example.com", "ID", "B124", 4.8, 7, 1500);

//         // Place manual bids
//         auction.placeBid(buyer1, 1100);
//         auction.placeBid(buyer2, 1200);

//         // Set auto-bid limits
//         auction.setAutoBidLimit(buyer1, 1300);
//         auction.setAutoBidLimit(buyer2, 1400);

//         // Trigger auto-bids with a manual bid
//         auction.placeBid(buyer1, 1250);

//         // Display auction details
//         auction.displayAuctionDetails();

//         // End the auction
//         auction.endAuction();
//         auction.deductWinnerCreditsAndRemoveItem(buyer2, items);
//         auction.displayAuctionDetails();

//         // Rate the participants
//         auction.rateParticipants(member4, buyer2, 5.0, 4.8);

//         // Save auction data to file
//         auction.saveAuctionData("auction_data.txt");

//         // Load auction data from file
//         try
//         {
//             Auction loadedAuction = Auction::loadAuctionData("auction_data.txt", items);
//             cout << "\nLoaded Auction Details:\n";
//             loadedAuction.displayAuctionDetails();
//         }
//         catch (const runtime_error &e)
//         {
//             cerr << e.what() << endl;
//         }
//     }

//     return 0;
// }

// ! Test Member Function
// #include <iostream>
// #include <vector>
// #include "Member.h"
// #include "Item.h"
// #include "functions/Function.h"

// using namespace std;

// int main() {
//     // File paths
//     const string membersFile = "members.txt";
//     const string itemsFile = "item.txt";

//     // Create a Member
//     Member member4("user1", "pass123", "John Doe", "1234567890", "john@example.com", "IDCard", "A12345678", 4.5, 10, 100);
//     Function::writeToFile(membersFile, member4.toString());
//     cout << "Member created and saved to file.\n";

//     // Display member information
//     cout << "Displaying member information:\n";
//     member4.showInfo();

//     // Update member information
//     cout << "\nUpdating member information:\n";
//     member4.updateInfo(membersFile);
//     member4.showInfo();

//     // Top up credits
//     cout << "\nTopping up credit points:\n";
//     member4.topupCredit(membersFile);
//     member4.showInfo();

//     // Create a listing
//     cout << "\nCreating a listing:\n";
//     member4.createListing(itemsFile);

//     // View all listings
//     cout << "\nViewing all listings:\n";
//     member4.viewListings(itemsFile);

//     // Search for items
//     cout << "\nSearching for items:\n";
//     member4.searchItems("Iphone15", "Electronic", -1, -1);

//     // Place a bid on an item
//     vector<Item> items = Item::readData(itemsFile);
//     if (!items.empty()) {
//         cout << "\nPlacing a bid on the first item:\n";
//         member4.placeBid(items[1], itemsFile, membersFile);
//     } else {
//         cout << "No items available for bidding.\n";
//     }

//     // Rate the member
//     cout << "\nRating the member:\n";
//     member4.rateMember(5.0);
//     member4.showInfo();

//     // Update the member in the file
//     member4.updateMemberInFile(membersFile);

//     return 0;
// }

// !Test Bid Class
// #include <iostream>
// #include <vector>
// #include "Bid.h"
// #include "functions/Function.h"
// using namespace std;

// int main() {
//     // Create Bid objects
//     Bid bid1("Room1","A",100,true);  // Active bid in Room1
//     Bid bid2("Room1","B",100,true);  // Active bid in Room1
//     Bid bid3("Room2","C",100,false); // Inactive bid in Room2

//     // Write bids to a file
//     string filePath = "bids.txt";
//     Function::writeToFile(filePath, bid1.toString());  // Save bids to file

//     // Read bids from the file and display
//     vector<Bid> loadedBids = Bid::readData(filePath);
    
//     cout << "Loaded bids from file:\n";
//     for (const Bid& bid : loadedBids) {
//         cout << bid.toString() << endl;
//     }

//     return 0;
// }

// !Test Member Class With placeBid
int main() {
    // File path for bid storage
    const string filePath = "bids.txt";

    // Clear or initialize the file
    ofstream clearFile(filePath, ios::trunc);
    clearFile.close();

    // Create a member with initial credit points
    Member member1("user1", "pass123", "John Doe", "1234567890", "john@example.com", "IDCard", "A12345678", 4.5, 10, 100);
    Member member2("user2", "pass456", "Jane Smith", "0987654321", "jane@example.com", "Passport", "B98765432", 4.8, 15, 200);

    // Test case 1: Member 1 places the first bid
    cout << "Test Case 1: Member 1 places the first bid\n";
    unordered_map<string, int> previousBids1; // No previous bids
    std::string auctionID1 = "A123";
    std::string auctionID2 = "A456";
    member1.placeBid(auctionID1, 001, 300, previousBids1, 300, filePath);
    cout << "Remaining credit points (Member 1): " << member1.getCreditPoints() << endl;

    // Test case 2: Member 1 updates the bid on the same auction
    cout << "\nTest Case 2: Member 1 updates the bid\n";
    member1.placeBid(auctionID1, 001, 400, previousBids1, 400, filePath);
    cout << "Remaining credit points (Member 1): " << member1.getCreditPoints() << endl;

    // Test case 3: Member 2 places a bid on the same auction
    cout << "\nTest Case 3: Member 2 places a new bid\n";
    unordered_map<string, int> previousBids2; // No previous bids for member 2
    member2.placeBid(auctionID1, 002, 80, previousBids2, 450, filePath);
    cout << "Remaining credit points (Member 2): " << member2.getCreditPoints() << endl;

    // Test case 4: Member 1 places a bid on a different auction
    cout << "\nTest Case 4: Member 1 places a bid on a different auction\n";
    member1.placeBid(auctionID2, 001, 100, previousBids1, 500, filePath);
    cout << "Remaining credit points (Member 1): " << member1.getCreditPoints() << endl;

    // Verify file content
    cout << "\nContent of bids.txt:\n";
    ifstream inFile(filePath);
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            cout << line << endl;
        }
        inFile.close();
    } else {
        cerr << "Error: Unable to open the file.\n";
    }

    return 0;
}

// !Test calculateBidDifference in Bid class
// int main() {
//     // Simulate previous bids
//     unordered_map<string, int> previousBids;

//     // Sample bids
//     int diffA1 = Bid::calculateBidDifference("A", 100, previousBids);
//     int diffB1 = Bid::calculateBidDifference("B", 200, previousBids);
//     int diffC1 = Bid::calculateBidDifference("C", 250, previousBids);

//     int diffA2 = Bid::calculateBidDifference("A", 300, previousBids);
//     int diffB2 = Bid::calculateBidDifference("B", 350, previousBids);

//     // Print results
//     cout << "A: New Bid = 300, Previous Bid = 100, Difference = " << diffA2 << endl;
//     cout << "B: New Bid = 350, Previous Bid = 200, Difference = " << diffB2 << endl;

//     return 0;
// }

// int main() {
//     // Create a Bid object
//     const string filePath = "bids.txt";

//     string auctionID = "A123";
//     int memberID = 101;
//     int activeBid = 200; // Some example bid amount
//     bool isActive = true; // Active bid status

//     Bid bid(auctionID, memberID, activeBid, isActive); // Assuming constructor like this

//     // Get the string representation of the bid
//     string bidString = bid.toString();
//     Function::writeToFile(filePath, bid.toString());

//     // Output the result to check if it's formatted correctly
//     cout << "Bid as string: " << bidString << endl;

//     // Check the expected output format
//     // Expected output: A123,101,200,true

//     return 0;
// }