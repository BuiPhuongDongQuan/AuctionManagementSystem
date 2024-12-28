#include "User.h"
#include <iostream>

using namespace std;

int main() {

    // Set the path to the user data file
    User::setUserData("user.txt");



    // Prompt user for login credentials
    // string username, password;
    // cout << "\nEnter your username: " << endl;
    // cin >> username;
    // cout << "Enter your password: " << endl;
    // cin >> password;

    // // Attempt login with the provided credentials
    // User::login(username, password);
    string username, password, fullname, phoneNumber, email, IDType, IDNumber;
    
    cout << "Enter your username: " <<endl;
    cin >> username;
    cin.ignore();
    
    cout << "Enter your password: " <<endl;
    cin >> password;
    cin.ignore();

    cout << "Enter your fullname: " <<endl;
    getline(cin, fullname);
    
    cout << "Enter your phoneNumber: " <<endl;
    cin >> phoneNumber;
    cin.ignore();


    cout << "Enter your email: " <<endl;
    cin >> email;
    cin.ignore();

    cout << "Enter your ID type (Citizen ID/Passport): " <<endl;
    cin >> IDType;
    cin.ignore();

    cout << "Enter your ID number: " <<endl;
    cin >> IDNumber;
    cin.ignore();

    User::guestRegister(username, password, fullname, phoneNumber, email, IDType, IDNumber, 0);
    
    return 0;
}