#ifndef USER_H
#define USER_H
#include <string>
#include <vector>
using namespace std;

class User{
    protected:
        static string user_data;
    private:
        int userID;
        string username;
        string password;
        string fullname;
        string phoneNumber;
        string email;
        string IDType;
        string IDNumber;
        double rating;
        int ratedTimes;
        int creditPoints;
        static vector<User> users;
    public:
        User();
        User(int userID, string username, string password, string fullname, string phoneNumber, string email, string IDType, string IDNumber, double rating, int ratedTimes, int creditPoints);

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
        static void guestRegister(string username, string password, string fullname, string phoneNumber, string email, string IDType, string IDNumber);
        static void readData();
};
#endif