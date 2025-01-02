#include "User.h"
#include "functions/Function.h"
#include <iostream>
using namespace std;

// Static members
string User::user_data = "";
vector<User>User::users;

User::User(){}

User::User(string username, string password, string fullname, string phoneNumber, string email,string IDType, string IDNumber, int creditPoints)
    : username(username), password(password), fullname(fullname), phoneNumber(phoneNumber), email(email), IDType(IDType), IDNumber(IDNumber), creditPoints(creditPoints){}

// Set user data file path
void User::setUserData(string filePath) {
    user_data = filePath;
}

// Getters
string User::getUsername(){
    return username;
}

string User::getPassword(){
    return password;
}

int User::getCreditPoints(){
    return creditPoints;
}

// Setters
void User::setUsername(string username){
    this->username = username;
}

void User::setPassword(string password){
    this->password = password;
}

void User::setCreditPoints(int creditPoints){
    this->creditPoints = creditPoints;
}

void User::readData(){
    users.clear();
    int countLine = Function::countLine(user_data);

    vector<string> username = Function::readCol(0, user_data, ',');
    vector<string> password = Function::readCol(1, user_data, ',');
    vector<string> fullname = Function::readCol(2, user_data, ',');
    vector<string> phoneNumber = Function::readCol(3, user_data, ',');
    vector<string> email = Function::readCol(4, user_data, ',');
    vector<string> IDType = Function::readCol(5, user_data, ',');
    vector<string> IDNumber = Function::readCol(6, user_data, ',');
    vector<string> creditPoints = Function::readCol(7, user_data, ',');
    
    // Ensure all columns have the same number of elements
    size_t rowCount = username.size();
    if (fullname.size() != rowCount || password.size() != rowCount || phoneNumber.size() != rowCount ||
        email.size() != rowCount || IDType.size() != rowCount || IDNumber.size() != rowCount ||
        creditPoints.size() != rowCount) {
        std::cerr << "Error: Columns have inconsistent lengths!" << std::endl;
        return;
    }

    // Populate the users vector with User objects
    for (size_t i = 0; i < rowCount; ++i) { 
        try {
            users.emplace_back(username[i], password[i], fullname[i], phoneNumber[i], email[i], 
                               IDType[i], IDNumber[i], stoi(creditPoints[i])); // Using std::stoi for int conversion
        } catch (const std::exception& e) {
            std::cerr << "Error processing row " << i << ": " << e.what() << std::endl;
            continue;  // Skip this row and continue with the next one
        }
    }
}

// Authentication function
bool User::authentication(string username, string password){
    return this->username == username && this->password == password;
}

// Method to retrieve a user by username
User* User::getUser(string username){
    for (auto& user: users){
        if(user.getUsername() == username){
            return &user;
        }
    }
    return nullptr; // Return null if username is not match
}

// Login function
void User::login(string username, string password){
    readData();
    User* user = getUser(username);
    if(user == nullptr){
        cout << "Username not found. Please register to begin." << endl;
    }else{
        // Authenticate the user
        if(user->authentication(username, password)){
            cout << "Welcome back " << username << endl;
            user->setUsername(username);
        }else{
            cout << "Login failed! Username or password is incorrect." << endl;
        }
    }
}

// Check password is strong or not
bool User::isStrongPassword(string password){
    if(password.length() < 8) return false;
    
    bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;
    for(char c : password){
        if(isupper(c)) hasUpper = true;
        if(islower(c)) hasLower = true;
        if(isdigit(c)) hasDigit = true;
        if(ispunct(c)) hasSpecial = true;
    }
    return hasUpper && hasLower && hasDigit && hasSpecial;
}

// check if a username already exists
bool User::usernameExist(string username){
    readData();
    for(const auto& user: users){
        if(user.username == username){
            return true;
        }
    }
    return false;
}

// Register function
void User::guestRegister(string username, string password, string fullname, string phoneNumber, string email, string IDType, string IDNumber, int creditPoints){
    int countLine = Function::countLine(user_data);
    // Ensure the username is unique
    while(usernameExist(username)== true){
        cout << "Error: Username already exists. Please choose a different username." << endl;
        cout << "Please enter another username: ";
        cin >> username;
    }
    // Ensure password is strong
    while(!isStrongPassword(password)){ 
        cout << "The password must be at least 8 characters long and include uppercase, lowercase, digits, and special characters." << endl;
        cout << "Please enter a stronger password: ";
        cin >> password;
    }
    int creditpoints = 0;
    string newMember = "\n" + username + "," + password + "," + fullname + "," + phoneNumber + "," + email + "," + IDType + "," + IDNumber + "," + to_string(creditPoints);
    Function::writeToFile(user_data, newMember);
}