// ! Test Item Function
// #include "Item.h"
// #include <iostream>
// #include <vector>
// #include <fstream>

// using namespace std;

// int main() {
//     // Set item data file
//     const string filePath = "item_data.txt";
//     Item::setItemData(filePath);

//     // Test constructor and display details
//     cout << "Testing constructor and displayDetails()\n";
//     Item item("Laptop", "Electronics", "A high-end gaming laptop", 
//             1000, 1000, 50, 2025, 1, 15, 12, 0, 0);
//     item.displayDetails();

//     // Test toString()
//     cout << "\nTesting toString()\n";
//     cout << "Item as string: " << item.toString();

//     // Test writeToFile()
//     cout << "\nTesting writeToFile()\n";
//     item.writeToFile(filePath, item.toString());

//     // Test readItemData()
//     cout << "\nTesting readItemData()\n";
//     Item::readItemData();
//     const vector<Item>& items = Item::getItems();
//     for (const auto& i : items) {
//         i.displayLimitedDetails();
//     }

//     // Test addListing()
//     cout << "\nTesting addListing()\n";
//     item.addListing();

//     // Test removeListing()
//     cout << "\nTesting removeListing()\n";
//     if (!item.removeListing()) {
//         cout << "Failed to remove listing.\n";
//     }

//     // Test isTimerDone()
//     cout << "\nTesting isTimerDone()\n";
//     if (item.isTimerDone()) {
//         cout << "Timer is done for the item.\n";
//     } else {
//         cout << "Timer is still running for the item.\n";
//     }

//     // Test startTimer() (commented to avoid long wait in tests)
//     // cout << "\nTesting startTimer()\n";
//     // item.startTimer();

//     // Test removeFromFile()
//     cout << "\nTesting removeFromFile()\n";
//     Item::removeFromFile(filePath, "Laptop");
//     Item::readItemData();
//     for (const auto& i : Item::getItems()) {
//         i.displayLimitedDetails();
//     }

//     // Cleanup
//     cout << "\nCleaning up test file\n";
//     remove(filePath.c_str());

//     cout << "\nAll tests completed.\n";
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
#include <iostream>
#include <vector>
#include "Bid.h"
#include "functions/Function.h"
using namespace std;

int main() {
    // Create Bid objects
    Bid bid1("Room1","A",100,true);  // Active bid in Room1
    Bid bid2("Room1","B",100,true);  // Active bid in Room1
    Bid bid3("Room2","C",100,false); // Inactive bid in Room2

    // Write bids to a file
    string filePath = "bids.txt";
    Function::writeToFile(filePath, bid1.toString());  // Save bids to file

    // Read bids from the file and display
    vector<Bid> loadedBids = Bid::readData(filePath);
    
    cout << "Loaded bids from file:\n";
    for (const Bid& bid : loadedBids) {
        cout << bid.toString() << endl;
    }

    return 0;
}
