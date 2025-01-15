#ifndef ADMIN_H
#define ADMIN_H
#include <string>
#include "User.h"
#include "Item.h"
using namespace std;

class Admin : public User{
    public:
        // Constructor
        // Admin();
        // Admin(string username, string password, string fullname, string phoneNumber, string email, string IDType, string IDNumber, int creditPoints);
        
        // Methods
        static void viewMemberInfo(string filePath);
        static void viewItemData(string filePath);
};
#endif