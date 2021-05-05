#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>
#include <string.h>

using namespace std;

// int* readArray(string fileName,int size);
// void setArray(string fileName, int* arr, int &size);
int* setIntArray(string fileName, int &size);
void sortInt(int a[], int n);
void mergeInt(int a[], int a1[], int a2[], int n);
void printIntMatches(int* arr1, int* arr2, int size1, int size2);
string* setStringArray(string fileName, int &size);
void sortString(string* a, int n);
void mergeString(string* a, string* leftA, string* rightA, int n);
void printStringMatches(string* arr1, string* arr2, int size1, int size2);

int main (int argc, char* argv[]) {
    string searchChoice = argv[1];
    ifstream inF1;
    ifstream inF2;
    string file1 = argv[2];
    string file2 = argv[3];

    inF1.open(argv[2]);
    inF2.open(argv[3]);


    if (!inF1.is_open()) {
        cout << "Failed to open \"" << argv[2]  << "\"" << endl;
    }
    else if (!inF2.is_open()) {
        cout << "Failed to open \"" << argv[3]  << "\"" << endl;
    }
    else if (argc != 4) {
        cout << "Incorrect number of funtion calls" << endl;
    }
    else if ( (searchChoice.length() != 1) && (searchChoice != "i" || searchChoice != "s")) {
        cout << "Unavailable data item searched" << endl;
    }
    else if (searchChoice == "i") {
        int* arr1,  *arr2;
        int size1, size2;
        arr1 = setIntArray(file1, size1);
        sortInt(arr1, size1);
        arr2 = setIntArray(file2, size2);
        sortInt(arr2, size2);
        printIntMatches(arr1, arr2, size1, size2);
    }
    else if (searchChoice == "s") {
        string* arr1, *arr2;
        int size1, size2;

        arr1 = setStringArray(file1, size1);
        //cout << size;
        sortString(arr1, size1);
        arr2 = setStringArray(file2, size2);
        sortString(arr2, size2);
        printStringMatches(arr1, arr2, size1, size2);
    }
    return 0;
}

void sortInt(int a[], int n) {
    if (n <= 1) {
        return;
    }

    int* leftA = new int[n/2];
    int* rightA = new int[n-(n/2)];
    for (int i = 0; i < n/2; i++){
        leftA[i] = a[i];
    }
    for (int i = n/2; i<n; i++) {
        rightA[i-n/2] = a[i];
    }
    sortInt(leftA, n/2);
    sortInt(rightA, n-n/2);
    mergeInt(a, leftA, rightA, n);
}

void mergeInt(int a[], int leftA[], int rightA[], int n) {
    int n1 = n/2; 
    int n2 = n-n/2;
    int p1 = 0;
    int p2 = 0;
    int i = 0;
    
    while (p1 < n1 && p2 < n2) {
        a[i++] = leftA[p1]<rightA[p2] ? leftA[p1++] : rightA[p2++];
    }
    
    while (p1 < n1) {
        a[i++] = leftA[p1++];
    }
    
    while (p2 < n2) { 
        a[i++] = rightA[p2++];
    }
}

void printIntMatches(int* arr1, int* arr2, int size1, int size2) {
    for (int i = 0; i < size1; i++) {
        if (i > 0 && arr1[i] == arr1[i-1]) {
            continue;
        }
        for (int j = 0; j < size2; j++) {
            if (arr1[i] == arr2[j]) {
                cout << arr1[i] << endl;
                break;
            }
            
        }
    }
}

int* setIntArray(string fileName, int &size) {
    size = 0;
    int a[20000];
    ifstream inF;
    inF.open(fileName);
    for (int i = 0; i < 20000; i++) {
        if (inF.eof()) {
            size--;
            break;
        }
        else {
            inF >> a[i];
            size++;
        }
    }
    inF.close();

    int* arr = new int[size];
    inF.open(fileName);

    for (int i = 0; i < size; i++) {
        inF >> arr[i];
    }

    inF.close();

    return arr;
}

string* setStringArray(string fileName, int &size) {
    size = 0;
    string a[20000];
    ifstream inF;
    inF.open(fileName);
    for (int i = 0; i < 20000; i++) {
        if (inF.eof()) {
            size--;
            break;
        }
        else {
            inF >> a[i];
            size++;
        }
    }
    inF.close();

    string* arr = new string[size];
    inF.open(fileName);

    for (int i = 0; i < size; i++) {
        inF >> arr[i];
    }
    inF.close();
    return arr;
}

void sortString(string* a, int n) {
    if (n <= 1) {
        return;
    }

    string* leftA = new string[n/2];
    string* rightA = new string[n-(n/2)];
    for (int i = 0; i < n/2; i++){
        leftA[i] = a[i];
    }
    for (int i = n/2; i<n; i++) {
        rightA[i-n/2] = a[i];
    }
    sortString(leftA, n/2);
    sortString(rightA, n-n/2);
    mergeString(a, leftA, rightA, n);
}

void mergeString(string* a, string* leftA, string* rightA, int n) {
    int n1 = n/2; 
    int n2 = n-n/2;
    int p1 = 0;
    int p2 = 0;
    int i = 0;

    
    while (p1 < n1 && p2 < n2) {
        a[i++] = leftA[p1]<rightA[p2] ? leftA[p1++] : rightA[p2++];
    }
    
    while (p1 < n1) {
        a[i++] = leftA[p1++];
    }
    
    while (p2 < n2) { 
        a[i++] = rightA[p2++];
    }
}

void printStringMatches(string* arr1, string* arr2, int size1, int size2) {
    for (int i = 0; i < size1; i++) {
        if (i > 0 && arr1[i] == arr1[i-1]) {
            continue;
        }
        for (int j = 0; j < size2; j++) {
            if (arr1[i] == arr2[j]) {
                cout << arr1[i] << endl;
                break;
            }
            
        }
    }
}