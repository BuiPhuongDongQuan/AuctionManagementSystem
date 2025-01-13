#ifndef ITEM_H
#define ITEM_H
using namespace std;

#include <string>
#include <vector>

class Item {
    protected:
        static string item_data;
    private:
        std::string itemName;
        std::string category;
        std::string description;
        int startingBid;
        int bidIncrement;
        long endDateTime; // Use long for simplicity (UNIX timestamp)
        double ratingPoints;
        static vector<Item> items;

    public:
        // Constructor
        Item(std::string name, std::string cat, std::string desc, int startBid, int increment, long end, double ratingPoints);
        
        // Methods
        void addListing();
        void displayDetails();
        static void readItemData();
        static void setItemData(string filePath);

        // Getters
        std::string getName() const;
        std::string getCategory() const;
        string getDescription()const;
        static string getItemData();
        static const vector<Item>& getItems();
};

#endif // ITEM_H