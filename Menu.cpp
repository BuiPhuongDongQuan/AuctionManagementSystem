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
string Menu::user_data = "members.txt";
string Menu::item_data = "item.txt";
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
    cout << "1. Guest  2. Member  3. Admin\n";
    int choice = Menu::handleUserInput(1, 3);

    switch (choice)
    {
    case 1:
        guestDashboard();
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
    cin.ignore();
    cout << "Enter your password: ";
    cin >> password;
    cin.ignore();
    member.login(username, password);
}

// Admin Login Menu
void Menu::adminLoginMenu(){
    string username, password;
    cout << "-----Admin Login-----\n";
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;
    cin.ignore(); // Clear buffer
    if(username == "admin" && password == "Admin123@!"){
        adminDashboard();
    }else{
        cout << "Wrong username or password, please login again!\n";
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
        Admin::viewItemData(item_data);
        adminDashboard();
        break;
    
    case 2:
        Admin::viewMemberInfo(user_data);
        adminDashboard();
        break;
    }
}

// Guest Dashboard

void Menu::guestDashboard(){
    cout << "-----Welcome-----\n";
    cout << "1. View Product Information\n";
    cout << "2. Register\n";
    int choice = Menu::handleUserInput(1, 2);
    switch (choice)
    {
    case 1:
        Guest::viewItem(item_data);
        guestDashboard();
        break;
    
    case 2:
        registerMenu();
        break;
    }
}

void Menu::registerMenu(){
    string username, password, fullname, phoneNumber, email, IDType, IDNumber;
    cout << "-----Register-----\n";
    cout << "Enter your username: ";
    cin >> username;
    cin.ignore();
    cout << "Enter your password: ";
    cin >> password;
    cin.ignore();
    cout << "Enter your full name: ";
    getline(cin,fullname);
    cout << "Enter your phone number: ";
    cin >> phoneNumber;
    cin.ignore();
    cout << "Enter your email: ";
    cin >> email;
    cin.ignore();
    cout << "Enter your ID Type: ";
    cin >> IDType;
    cin.ignore();   
    cout << "Enter your ID Number: ";
    cin >> IDNumber;
    cin.ignore();

    User::guestRegister(username, password, fullname, phoneNumber, email, IDType, IDNumber);
}

// Member Dashboard
void Menu::memberDashboard(){
    cout << "-----Member Dashboard-----\n";
    cout << "This is your menu:\n";
    cout << "1. View your infomation\n";
    cout << "2. Update infomation\n";
    cout << "3. Top up credit points\n";
    cout << "4. Creating item\n";
    int choice = Menu::handleUserInput(1, 4);
    switch (choice)
    {
    case 1:
        memberInfoDashboard();
        break;
    case 2:
        memberUpdateDashboard();
        break;
    case 3:
        memberTopupDashboard();
        break;
    case 4:
        member.createListing(member.getUsername());
        Menu::memberDashboard;
    default:
        break;
    }
}

void Menu::memberInfoDashboard(){
    member.showInfo(member.getUsername());
    Menu::memberDashboard();
}

void Menu::memberUpdateDashboard(){
    cout << "========= UPDATE MEMBER INFORMATION =========\n";
    cout << "Select the field you want to update:\n";
    cout << "1. Full Name\n";
    cout << "2. Username\n";
    cout << "3. Password\n";
    cout << "4. Email\n";
    cout << "5. Phone Number\n";
    cout << "6. ID Type\n";
    cout << "7. ID Number\n";
    cout << "8. Exit\n";
    int choice = Menu::handleUserInput(1, 8);
    member.updateInfo(choice, member.getUsername());
}

void Menu::memberTopupDashboard(){
    member.topupCredit(member.getUsername());
    Menu::memberDashboard();
}