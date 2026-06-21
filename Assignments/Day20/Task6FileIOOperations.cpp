/* 
Task 6: File I/O Operations
Objective: Perform basic file input and output operations.
Steps:
Write a function to create a text file and write a few lines.
Read the contents of the file and print them to the console. */

#include <iostream>
#include <fstream>  
#include <string>

using namespace std;

void writeToFile(string filename) {
    ofstream outFile(filename);

    if (outFile.is_open()) {
        outFile << "Line 1: Hello from C++ File I/O!" << endl;
        outFile << "Line 2: This file was created dynamically." << endl;
        outFile << "Line 3: Closing the file now." << endl;
        outFile.close();
        cout << "Successfully wrote to " << filename << endl;
    } else {
        cerr << "Error: Could not create file." << endl;
    }
}

void readFromFile(string filename) {
    // ifstream = Input File Stream (Reading)
    ifstream inFile(filename);
    string line;

    if (inFile.is_open()) {
        cout << "\n--- Reading File Contents ---" << endl;
        while (getline(inFile, line)) {
            cout << line << endl;
        }
        inFile.close();
    } else {
        cerr << "Error: Could not open file for reading." << endl;
    }
}

int main() {
    string myFile = "example.txt";

    writeToFile(myFile);
    readFromFile(myFile);

    return 0;
}
