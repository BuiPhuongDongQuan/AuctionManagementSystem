#include "Menu.h"
#include <iostream>
#include <memory>

using namespace std;

// Initialize static variables
User Menu::user;
Admin Menu::admin;
Guest Menu::guest;
Member Menu::member;
Item Menu::item;

// User input their choice
int Menu::handleUserInput(int min, int max){
    int choice;
    while (true) {
        try {
            cout << "Enter Your Choice (" << min << "-" << max << "): ";
            string input;
            getline(cin, input); // Read input as a string

            // Convert input to an integer
            choice = std::stoi(input);

            // Check if the choice is within range
            if (choice >= min && choice <= max) {
                break; // Valid input, exit the loop
            } else {
                cout << "Invalid choice. Please enter a number between " 
                        << min << " and " << max << "." << endl;
            }
        } catch (const invalid_argument&) {
            cout << "Invalid input. Please enter a valid number." << endl;
        } catch (const out_of_range&) {
            cout << "Number is out of range. Please try again." << endl;
        }
    }

    return choice;
}

// User choose their role
void Menu::menuDisplay(){
    cout << "EEET2482/COSC2082 GROUP ASSIGNMENT\n";
    cout << "Semester 3 2024\n";
    cout << "AUCTION APPLICATION\n\n";
    cout << "AUCTION APPLICATION\n";
    cout << "Group: Group No.\n";
    cout << "XXXXXXX, Student Name\n";
    cout << "XXXXXXX, Student Name\n";
    cout << "XXXXXXX, Student Name\n";
    cout << "XXXXXXX, Student Name\n\n";
    cout << "-----Choose Your Role-----\n";
    cout << "Please let us know who you are: \n";
    cout << "1. Guest\n 2. Member\n 3. Admin\n";
    int choice = Menu::handleUserInput(1, 3);

    switch (choice)
    {
    case 1:
        // guestDasboard();
        break;
    
    case 2:
        loginMenu();
        break;
    
    case 3:
        adminLoginMenu();
        break;
    }
}

// Login Menu
void Menu::loginMenu(){
    string username, password;
    cout << "-----Login-----\n";
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;
    User::login(username, password);
}

// Admin Login Menu
void Menu::adminLoginMenu(){
    string username, password;
    cout << "-----Admin Login-----\n";
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;
    User::readData();
    if(username == "admin" && password == "Admin123@!"){
        adminDashboard();
    }else{
        cout << "Wrong username or password, please login again!";
        adminLoginMenu();
    }
}

// Admin Dashboard
void Menu::adminDashboard(){
    cout << "-----Welcome to Admin Dashboard-----\n";
    cout << "1. View All Items Data\n";
    cout << "2. View All Member Infomation\n";
    int choice = Menu::handleUserInput(1, 2);
    switch (choice)
    {
    case 1:
        Admin::viewItemData();
        adminDashboard();
        break;
    
    case 2:
        Admin::viewMemberInfo();
        adminDashboard();
        break;
    }
}