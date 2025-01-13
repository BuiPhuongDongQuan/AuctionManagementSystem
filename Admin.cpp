#include "Admin.h"
#include "functions/Function.h"
#include <iostream>
#include <fstream>
using namespace std;

// Admin::Admin() : User(){}
// Admin::Admin(string username, string password, string fullname, string phoneNumber, string email, string IDType, string IDNumber, int creditPoints) : User(username, password, fullname, phoneNumber, email, IDType, IDNumber, creditPoints){}

void Admin::viewMemberInfo() const{
    readData();
    ifstream file(User::user_data);
    if(!file.is_open()){
        cerr << "Error: Cannot open file." << endl;
        return;
    }

    string line;
    cout << "User Data: " << endl;

    // Read and display each line in file

    while(getline(file, line)){
        cout << line << endl;
    }

    file.close();
}

void Admin::viewItemData() const{
    Item::readItemData();
    ifstream file(Item::getItemData());
    if(!file.is_open()){
        cerr << "Error: Cannot open file." << endl;
        return;
    }

    string line;
    cout << "Item Data: " << endl;

    // Read and display each line in file
    while(getline(file, line)){
        cout << line << endl;
    }

    file.close();
}
