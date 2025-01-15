#ifndef Menu_H
#define Menu_H
#include "User.h"
#include "Member.h"
#include "Guest.h"
#include "Admin.h"
#include "Item.h"
#include "Rating.h"
#include <memory>
using namespace std;
class Menu{
    public:
        static User user;
        static Admin admin;
        static Member member;
        static Guest guest;
        static Item item;
        static Rating rating;
        
        // File path
        const string membersFile = "members.txt";
        const string itemsFile = "item.txt";

        // Menu-related functions
        static int handleUserInput(int min, int max);
        static void menuDisplay();
        static void loginMenu();
        static void adminLoginMenu();
        static void registerMenu();
        static void adminDashboard();
        static void guestDashboard();
};
#endif