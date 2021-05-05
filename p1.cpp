#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>
#include <iomanip>
#include <bits/stdc++.h>


using namespace std;

void printHelp();
void print(string fileName, int width);
void cols(int width, ifstream& inStr, string str);
void searchNew(int width, string colName, string colVal, string fileName);
void min(string colName, string fileName);
void max(string colName, string fileName);
void avg(string colName, string fileName);

int main(int argc, char* argv[]) {
    string choice;
    ifstream inF;
    int counter = 0;
    int width = atoi(argv[2]);
    
    inF.open(argv[1]);
    if (argc != 3) {
        cout << "Usage: ./a database.csv #col_width" << endl;
    }
    else if (!inF.is_open()) {
        cout << "Failed to open \"" << argv[1]  << "\"" << endl;
    }
    else {
        cout << "Enter a command or \"help\" for a command list:" << endl;
        getline(cin, choice);
        while (1) {
            if (counter > 0) {
                cout << "Enter a command or \"help\" for a command list:" << endl;
                getline(cin, choice);
            }
            if (choice == "quit") {
                break;
            }
            else if (choice == "help") {
                printHelp();
            }
            else if (choice == "print") {
                inF.clear();
                print(argv[1], width);
            }
            else if (choice == "cols") {
                cols(width, inF, argv[1]);
            }
            else if (choice.find("search") != string::npos) {
                istringstream iss;
                iss.str(choice);
                
                string colName, colVal, search;
                getline(iss, search, ' ');
                iss >> quoted(colName);
                iss >> quoted(colVal);
                searchNew(width, colName, colVal, argv[1]);
            } 
            else if (choice.find("min") != string::npos) {
                istringstream iss;
                iss.str(choice);
                string colName, mini;
                getline(iss, mini, ' ');
                iss >> quoted(colName);
                min(colName, argv[1]);
            }
            else if (choice.find("max") != string::npos) {
                istringstream iss;
                iss.str(choice);
                string colName, maxi;
                getline(iss, maxi, ' ');
                iss >> quoted(colName);
                max(colName, argv[1]);
            }
            else if (choice.find("avg") != string::npos) {
                istringstream iss;
                iss.str(choice);
                string colName, maxi;
                getline(iss, maxi, ' ');
                iss >> quoted(colName);
                avg(colName, argv[1]);
            }
            else {
                cout << "Invalid command" << endl;
            }
            counter++;
        }
    }
    inF.close();
    return 0;
}

void print(string fileName, int width) {
    ifstream inF;
    inF.open(fileName);
    string line;
    string arr[5000][50];
    int row, col, counter = 0;
    for (int r = 0; r < 5000; r++) {
        if (counter == 0) {
            for (int c = 0; c < 50; c++) {
                getline(inF, arr[r][c], ',');
                if (arr[r][c].find('\n') != string :: npos) {
                    string temp = arr[r][c];
                    arr[r][c] = arr[r][c].substr(0, arr[r][c].find('\n'));
                    arr[r+1][0] = temp.substr(temp.find('\n') + 1, temp.find(',')); 
                    break;
                }
            }
        }
        else if (counter > 0) {
            for (int c = 1; c < 50; c++) {
                getline(inF, arr[r][c], ',');
                if (arr[r][c].find('\n') != string :: npos) {
                    string temp = arr[r][c];
                    arr[r][c] = arr[r][c].substr(0, arr[r][c].find('\n'));
                    arr[r+1][0] = temp.substr(temp.find('\n') + 1, temp.find(',')); 
                    col = c + 1; 
                    break;
                }
            }
        }
        counter++;
        if (inF.eof()) {
            inF.close();
            row = r + 1;
            break;
        }
    }
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < col; c++) {
            if (c == col - 1) {
                cout << right << setw(width) << arr[r][c] << endl;
                break;
            }
            cout << right << setw(width) << arr[r][c];

        }
    } 
}

void cols(int width, ifstream& inStr, string str) {
    string arr[5000][50];
    for (int c = 0; c < 50; c++) {
        getline(inStr, arr[0][c], ',');
        if (arr[0][c].find('\n') != string :: npos) {
            arr[0][c] = arr[0][c].substr(0, arr[0][c].find('\n'));
            cout <<  arr[0][c] << endl;
            break;
        }
        cout << arr[0][c] << endl;
    } 
    inStr.close();
    inStr.open(str);
}

void printHelp () {
    cout << "command list:" << endl << "\tprint" << endl << "\tcols" << endl << "\tsearch *|col_name val" << endl << "\tmin col_name" << endl << "\tmax col_name" << endl << "\tavg col_name" << endl;
}

void searchNew(int width, string colName, string colVal, string fileName) {
    string arr[5000][50];
    ifstream inStr;
    int colCheck;
    inStr.open(fileName);
    int row, col, counter = 0;
    int matches = 0;
    for (int r = 0; r < 5000; r++) {
        if (counter == 0) {
            for (int c = 0; c < 50; c++) {
                getline(inStr, arr[r][c], ',');
                if (arr[r][c].find('\n') != string :: npos) {
                    string temp = arr[r][c];
                    arr[r][c] = arr[r][c].substr(0, arr[r][c].find('\n'));
                    arr[r+1][0] = temp.substr(temp.find('\n') + 1, temp.find(',')); 
                    break;
                }
            }
        }
        else if (counter > 0) {
            for (int c = 1; c < 50; c++) {
                getline(inStr, arr[r][c], ',');
                if (arr[r][c].find('\n') != string :: npos) {
                    string temp = arr[r][c];
                    arr[r][c] = arr[r][c].substr(0, arr[r][c].find('\n'));
                    arr[r+1][0] = temp.substr(temp.find('\n') + 1, temp.find(',')); 
                    col = c + 1; 
                    break;
                }
            }
        }
        counter++;
        if (inStr.eof()) {
            inStr.close();
            row = r + 1;
            break;
        }
    }

    for (int c = 0; c < 50; c++) {
        if (arr[0][c].find(colName) != string ::npos) {
            colCheck = c;
        }
    }

    if (colName == "*") {
        for (int r = 1; r < row; r++) {
            for (int c = 0; c < col; c++) {
                if (arr[r][c] == colVal) {
                    matches++;
                }
            }
            
        }
        if (matches == 0) {
            cout << "No results" << endl;
        }
        else {
            for (int c = 0; c < col; c++) {
                if (c == col - 1) { 
                    cout << right << setw(width) << arr[0][c] << endl;
                    break;
                }
                cout << right << setw(width) << arr[0][c];
            }
            for (int r = 1; r < row; r++) {
                for (int c = 0; c < col; c++) {
                    if (arr[r][c] == colVal) {
                        for (int k = 0; k < col; k++) {
                            cout << right << setw(width) << arr[r][k];
                            if (k == col - 1) {
                                cout << endl;
                            }
                        }
                        break;
                    }
                }
            }
        }
    }
    else if (arr[0][colCheck].find(colName) == string :: npos) {
        cout << "Invalid column \""<< colName << "\"" << endl;
    }
    else {
        for (int r = 1; r < row;) {
            if (arr[r][colCheck].compare(colVal) == 0) {
                for (int c = 0; c < col; c++) {
                    if (c == col - 1) {
                        matches++;
                    }
                }
            }
            r++;
        }
        if (matches == 0) {
            cout << "No results" << endl;
        }
        else { 
            for (int c = 0; c < col; c++) {
                if (c == col - 1) { 
                    cout << right << setw(width) << arr[0][c] << endl;
                    break;
                }
                cout << right << setw(width) << arr[0][c];
            }
            for (int r = 1; r < row;) {
                if (arr[r][colCheck].compare(colVal) == 0) {
                    for (int c = 0; c < col; c++) {
                        cout << right << setw(width) << arr[r][c];
                        if (c == col - 1) {
                            cout << endl;
                        }
                    }
                }
                r++;
            }
        }
    }
}

void min(string colName, string fileName) {
    double min = INT_MAX;
    string arr[5000][50];
    bool na = false;
    int nonempties = 0;
    ifstream inStr;
    int colCheck;
    inStr.open(fileName);
    int row, counter = 0;

    for (int r = 0; r < 5000; r++) {
        if (counter == 0) {
            for (int c = 0; c < 50; c++) {
                getline(inStr, arr[r][c], ',');
                if (arr[r][c].find('\n') != string :: npos) {
                    string temp = arr[r][c];
                    arr[r][c] = arr[r][c].substr(0, arr[r][c].find('\n'));
                    arr[r+1][0] = temp.substr(temp.find('\n') + 1, temp.find(',')); 
                    break;
                }
            }
        }
        else if (counter > 0) {
            for (int c = 1; c < 50; c++) {
                getline(inStr, arr[r][c], ',');
                if (arr[r][c].find('\n') != string :: npos) {
                    string temp = arr[r][c];
                    arr[r][c] = arr[r][c].substr(0, arr[r][c].find('\n'));
                    arr[r+1][0] = temp.substr(temp.find('\n') + 1, temp.find(','));  
                    break;
                }
            }
        }
        counter++;
        if (inStr.eof()) {
            inStr.close();
            row = r + 1;
            break;
        }
    }
    for (int c = 0; c < 50; c++) {
        if (arr[0][c].find(colName) != string ::npos) {
            colCheck = c;
        }
    }
    if (arr[0][colCheck].find(colName) == string :: npos) {
        cout << "Invalid column \""<< colName << "\"" << endl;
    }
    else {
        for (int r = 1; r < row;) {
            for (int c = colCheck; c < colCheck + 1; c++) {
                if (!arr[r][colCheck].empty()) {
                    nonempties++;
                    break;
                }
            }
            r++;
        }
        if (nonempties == 0) {
            na = true;
        }
        for (int r = 1; r < row;) {
            if (arr[r][colCheck].empty()) {
                r++;
            }
            else {
                for (int c = colCheck; c < colCheck + 1; c++) {
                    double x;
                    stringstream converter(arr[r][colCheck]);
                    converter >> x;
                    if (x < min) {
                        min = x;
                    }
                }
                r++;
            }
        }
        if (na == true) {
            cout << "The min for col \"" << colName << "\" = N/A" << endl;
        }
        else {
            cout << "The min for col \"" << colName << "\" = " << min << endl;
        }
    }
}

void max(string colName, string fileName) {
    double max = INT_MIN;
    string arr[5000][50];
    bool na = false;
    int nonempties = 0;
    ifstream inStr;
    int colCheck;
    inStr.open(fileName);
    int row, counter = 0;

    for (int r = 0; r < 5000; r++) {
        if (counter == 0) {
            for (int c = 0; c < 50; c++) {
                getline(inStr, arr[r][c], ',');
                if (arr[r][c].find('\n') != string :: npos) {
                    string temp = arr[r][c];
                    arr[r][c] = arr[r][c].substr(0, arr[r][c].find('\n'));
                    arr[r+1][0] = temp.substr(temp.find('\n') + 1, temp.find(',')); 
                    break;
                }
            }
        }
        else if (counter > 0) {
            for (int c = 1; c < 50; c++) {
                getline(inStr, arr[r][c], ',');
                if (arr[r][c].find('\n') != string :: npos) {
                    string temp = arr[r][c];
                    arr[r][c] = arr[r][c].substr(0, arr[r][c].find('\n'));
                    arr[r+1][0] = temp.substr(temp.find('\n') + 1, temp.find(','));
                    break;
                }
            }
        }
        counter++;
        if (inStr.eof()) {
            inStr.close();
            row = r + 1;
            break;
        }
    }
    for (int c = 0; c < 50; c++) {
        if (arr[0][c].find(colName) != string ::npos) {
            colCheck = c;
        }
    }
    if (arr[0][colCheck].find(colName) == string :: npos) {
        cout << "Invalid column \""<< colName << "\"" << endl;
    }
    else {
        for (int r = 1; r < row;) {
            for (int c = colCheck; c < colCheck + 1; c++) {
                if (!arr[r][colCheck].empty()) {
                    nonempties++;
                    break;
                }
            }
            r++;
        }
        if (nonempties == 0) {
            na = true;
        }
        for (int r = 1; r < row;) {
            for (int c = colCheck; c < colCheck + 1; c++) {
                double x;
                stringstream converter(arr[r][colCheck]);
                converter >> x;
                if (x > max) {
                    max = x;
                }
            }
            r++;
        }
        if (na == true) {
            cout << "The max for col \"" << colName << "\" = N/A" << endl;
        }
        else {
            cout << "The max for col \"" << colName << "\" = " << max << endl;
        }
    }
}

void avg(string colName, string fileName) {
    double avg = 0;
    string arr[5000][50];
    bool na = false;
    int nonempties = 0;
    ifstream inStr;
    int colCheck;
    inStr.open(fileName);
    int row, counter = 0;

    for (int r = 0; r < 5000; r++) {
        if (counter == 0) {
            for (int c = 0; c < 50; c++) {
                getline(inStr, arr[r][c], ',');
                if (arr[r][c].find('\n') != string :: npos) {
                    string temp = arr[r][c];
                    arr[r][c] = arr[r][c].substr(0, arr[r][c].find('\n'));
                    arr[r+1][0] = temp.substr(temp.find('\n') + 1, temp.find(',')); 
                    break;
                }
            }
        }
        else if (counter > 0) {
            for (int c = 1; c < 50; c++) {
                getline(inStr, arr[r][c], ',');
                if (arr[r][c].find('\n') != string :: npos) {
                    string temp = arr[r][c];
                    arr[r][c] = arr[r][c].substr(0, arr[r][c].find('\n'));
                    arr[r+1][0] = temp.substr(temp.find('\n') + 1, temp.find(',')); 
                    break;
                }
            }
        }
        counter++;
        if (inStr.eof()) {
            inStr.close();
            row = r + 1;
            break;
        }
    }
    for (int c = 0; c < 50; c++) {
        if (arr[0][c].find(colName) != string ::npos) {
            colCheck = c;
        }
    }
    if (arr[0][colCheck].find(colName) == string :: npos) {
        cout << "Invalid column \""<< colName << "\"" << endl;
    }
    else {
        for (int r = 1; r < row;) {
            for (int c = colCheck; c < colCheck + 1; c++) {
                if (!arr[r][colCheck].empty()) {
                    nonempties++;
                    break;
                }
            }
            r++;
        }
        if (nonempties == 0) {
            na = true;
        }
        for (int r = 1; r < row;) {
            for (int c = colCheck; c < colCheck + 1; c++) {
                double x;
                if (arr[r][colCheck].empty()) {
                    continue;
                }
                else {
                stringstream converter(arr[r][colCheck]);
                converter >> x;
                avg += x;
                }
            }
            r++;
        }
        cout << avg << endl;
        avg = avg / nonempties;
        
        if (na == true) {
            cout << "The avg for col \"" << colName << "\" = N/A" << endl;
        }
        else {
            cout << "The avg for col \"" << colName << "\" = " << avg << endl;
        }
    }
}