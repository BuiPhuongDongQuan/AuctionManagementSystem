#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Function.h"

using namespace std;


int Function::countLine(string filePath){
    int lines = 0;
    ifstream file(filePath);
    if(file.is_open()){
        string line;
        //Read each line in file    
        while(getline(file, line)){ 
            lines++;
        }
        file.close();
    }else{
        cerr << "Error: cannot open file" << filePath << endl;
    }
    return lines;
}

vector<string>Function::readCol(int col, const string& filePath, char delimiter){
    vector<string> colData;
    string  currentLine; 

    try {
        ifstream file(filePath);

        if(!file.is_open()){
            cerr << "Cannot open file" << filePath << endl;
            return {};
        }

        while(getline(file, currentLine)){
            stringstream ss(currentLine);
            string token;
            int currentCol = 0;

            //Split the line by the delimiter
            while(getline(ss, token, delimiter)){
                if(currentCol == col){
                    colData.push_back(token);
                    break;
                }
                ++currentCol;
            }
        }

        file.close();
    }catch(exception& e){
        cerr << "Error: " << e.what() << endl;
        return{};
    }
    if(!colData.empty()){
        colData.erase(colData.begin());
    }
    return colData; 
}

void Function::writeToFile(string filePath, string content){
    try{
        // Open file in append mode
        ofstream file(filePath, ios::app);
        if(!file.is_open()){
            throw ios_base::failure("Fail to open file.");
        }
        // Write content to file
        file << content;

        file.close();
    }catch(exception& e){
        throw runtime_error(string("Error writing to file") + e.what());
    }
}

void Function::readAllLine(const string filePath){
    try{
        // Open file
        ifstream file(filePath);
        if(!file.is_open()){
            throw ios_base::failure("Fail to open file.");
        }
        string line;
        while(getline(file,line)){ // Read line by line
            cout << line << endl;
        }
        file.close();
    } catch(const ios_base::failure& e){
        cerr << "An error occurred: " << e.what() << endl;
    }
}

void Function::modifyFile(const std::string& filePath, const std::string& oldString, const std::string& newString) {
    std::ifstream fileToBeModified(filePath);
    if (!fileToBeModified.is_open()) {
        std::cerr << "Error: Could not open file " << filePath << " for reading.\n";
        return;
    }

    // Read all lines of the file into oldContent
    std::string oldContent;
    std::string line;
    while (std::getline(fileToBeModified, line)) {
        oldContent += line + "\n";  // Preserve newline characters
    }
    fileToBeModified.close();

    // Replace all occurrences of oldString with newString
    size_t pos = 0;
    bool found = false;
    while ((pos = oldContent.find(oldString, pos)) != std::string::npos) {
        found = true;
        oldContent.replace(pos, oldString.length(), newString);
        pos += newString.length();
    }

    // Debug: Check if the old string was found
    if (!found) {
        std::cerr << "Error: Old string not found in the file.\n";
        return;
    }

    // Write the modified content back to the file
    std::ofstream writer(filePath);
    if (!writer.is_open()) {
        std::cerr << "Error: Could not open file " << filePath << " for writing.\n";
        return;
    }

    writer << oldContent;
    writer.close();

    std::cout << "File successfully updated.\n";
}

vector<string> Function::split(const string& str, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

string Function::vectorToCSVString(const vector<string>& data) {
    string csvString;
    for (size_t i = 0; i < data.size(); ++i) {
        csvString += data[i];
        if (i < data.size() - 1) {
            csvString += ",";
        }
    }
    return csvString;
}