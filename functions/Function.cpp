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