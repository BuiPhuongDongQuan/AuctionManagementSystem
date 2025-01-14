#include "Item.h"
#include "Member.h"
#include <iostream>
#include <ctime> // For time manipulation

void testItemClass() {
    // Set up
    Item sampleItem("Laptop", "Electronics", "High-performance gaming laptop", 100, 10,
                    2025, 1, 15, 23, 59, 59); // Bidding ends on 2025-01-15 23:59:59

    string filePathItem = "item.txt";

    sampleItem.writeToFile(filePathItem, sampleItem.toString());
    Member member("john_doe", "password123", "John Doe", "1234567890", "john@example.com", "ID", "1234", 4.5, 100, 100);
    
    string searchName;
    string searchCategory;
    int minBid = -1;
    int maxBid = -1;

    cout << "Enter the search criteria:\n";
    cout << "Name (leave empty for no search by name): ";
    getline(cin, searchName);
    
    cout << "Category (leave empty for no search by category): ";
    getline(cin, searchCategory);

    cout << "Min Bid (enter -1 for no min bid): ";
    cin >> minBid;

    cout << "Max Bid (enter -1 for no max bid): ";
    cin >> maxBid;

    // Call the searchItems method with the user input
    member.searchItems(searchName, searchCategory, minBid, maxBid);

}

int main() {
    testItemClass();
    return 0;
}
