#ifndef USER_H
#define USER_H
#include <string>
#include <vector>
using namespace std;

class User{
    private:
        static string user_data;
        string username;
        string password;
        string fullname;
        string phoneNumber;
        string email;
        string IDType;
        string IDNumber;
        int creditPoints;
        static vector<User> users;
    
    public:
        User();
        User(string username, string password, string fullname, string phoneNumber, string email, string IDType, string IDNumber, int creditPoints );

        // Getters
        string getUsername();
        string getPassword();
        int getCreditPoints();

        // Setters
        void setUsername(string username);
        void setPassword(string password);
        void setCreditPoints(int creditPoints);

        // Methods
        bool authentication(string username, string password);
        static bool usernameExist(string username);
        static bool isStrongPassword(string password);
        static User* getUser(string username);
        static void login(string username, string password);
        static void guestRegister(string username, string password, string fullname, string phoneNumber, string email, string IDType, string IDNumber, int creditPoints);
        static void readData();
        static void setUserData(string filPath);
};
#endif