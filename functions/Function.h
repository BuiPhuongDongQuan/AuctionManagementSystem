#ifndef FUNCTION_H
#define FUNCTION_H

#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

class Function{
    public:
        static int countLine(string filePath);
        static vector<string> readCol(int col, const string& filePath, char delimiter);
        static void writeToFile(string filePath, string content);
        static void readAllLine(string filePath);
};
#endif