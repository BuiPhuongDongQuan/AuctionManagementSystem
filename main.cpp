// ! Test Item Function
#include "Item.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int main() {
    // Set item data file
    const string filePath = "item.txt";
    Item::setItemData(filePath);

    // Test constructor and display details
    Item item(1, "Laptop", "Electronics", "A high-end gaming laptop", 
               1000, 1000, 50, 4.5, 2025, 1, 15, 12, 0, 0);
    Item item2(2, "Smartphone", "Electronics", "A flagship smartphone", 
               800, 800, 25, 3.0, 2025, 2, 1, 10, 30, 0);

    // Test toString()
    cout << "\nTesting toString()\n";
    cout << "Item as string: " << item.toString();
    cout << "Item as string: " << item2.toString();

    // Test writeToFile()
    cout << "\nTesting writeToFile()\n";
    Item::writeToFile(filePath, item.toString());
    Item::writeToFile(filePath, item2.toString());

    // Simulate a buyer with rating 3.5
    double buyerRating = 3.5;
    cout << "Items visible to buyer with rating " << buyerRating << ":\n";
    vector<Item> visibleItems = Item::getVisibleItems(buyerRating);
    Item::displayItems(visibleItems);

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
    return 0;
}

// ! Test Member Function

// #include <iostream>
// #include <vector>
// #include "Member.h"
// #include "Item.h"
// #include "Auction.h"
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
