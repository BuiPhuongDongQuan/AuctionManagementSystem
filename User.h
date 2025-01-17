#ifndef USER_H
#define USER_H
#include <string>
#include <vector>
using namespace std;

class User{
    protected:
        static string user_data;
        static vector<User> users;
    private:
        string userID;
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
    public:
        User();
        User(string userID, string username, string password, string fullname, string phoneNumber, string email, string IDType, string IDNumber, double rating, int ratedTimes, int creditPoints);
        
        // Getters
        string getUserID() const;
        string getUsername() const;
        string getPassword() const;
        string getFullname() const;
        string getPhoneNumber() const;
        string getEmail() const;
        string getIDType() const;
        string getIDNumber() const;
        double getRating() const;
        int getRatedTimes() const;
        int getCreditPoints() const;

        // Setters
        void setUsername(string username);
        void setPassword(string password);
        void setCreditPoints(int creditPoints);

        // Methods
        string toString() const;
        bool authentication(string username, string password);
        static bool usernameExist(string username);
        static bool isStrongPassword(string password);
        static User* getUser(string username);
        static void login(string username, string password);
        static void guestRegister(string username, string password, string fullname, string phoneNumber, string email, string IDType, string IDNumber);
        static void readData();

};
#endif