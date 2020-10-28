#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
                                // This program reads a random assortment of words and symbols and makes a message about an appointment from the info it gathers
bool Name(char str[]);          // This function checks to see if the first letter is uppercase, that there are no special characters, and every chaacter following the first is a lowercase letter 
bool Building(char str[]);      // This function checks to see if a string is 6 characters or longer, as well as, if there are 3-4 uppercase letters at the beginning and and the rest of the characters after that are numbers 
bool Date(char str[]);          // This function checks to see if a string is 5 characters long, and if the 3rd character is a '-', as well as, if the other characters are numbers 
bool Time(char str[]);          // This function checks to see if a string is 3-4 characters long, and if the string contains only numbers and the characters 'am' or 'pm' which denote the time of day

int main() {
    char str[100] = " ";
    char name[100] = "<not provided>";
    char date[100] = "<not provided>";
    char time[100] = "<not provided>";
    char build[100] = "<not provided>";
    bool isValidDate = false;
    bool isValidName = false;
    bool isValidTime = false;
    bool isValidBuild = false;
    while (!feof(stdin)) {
        scanf("%s", str); 
        if (!isValidDate && Date(str) == true) {
            strcpy(date, str);
            isValidDate = true;
        }
        else if (!isValidName && Name(str) == true) {
            strcpy(name, str);
            isValidName = true;
        }
        else if (!isValidTime && Time(str) == true) {
            strcpy(time, str);
            isValidTime = true;
        }
        else if (!isValidBuild && Building(str)== true) {
            strcpy(build, str);
            isValidBuild = true;
        }
    }   
    printf("Appointment with %s is on %s at %s in %s\n", name, date, time, build);

    return 0;
}

bool Name(char str[]) {
        int len = strlen(str);
        if (isupper(str[0])) {       
            for (int i = (len - 1); i > 0; --i) {
                char ch = str[i]; 
                if (!islower(ch) || !isalpha(ch)) {
                    return false;
                }
            }
            return true;
        }
    return false;
}
bool Building(char str[]) {
    int len = strlen(str);
    if (len >= 6) {
        if ((isupper(str[0]) && isupper(str[1]) && isupper(str[2])) &&
           ((isdigit(str[3]) || isupper(str[3])) && isdigit(str[4]))) {
            for (int i = (len - 1); i >= 4; --i) {
                if(!isdigit(str[i])) {
                    return false;
                }
                else{
                    return true;
                }
            }
        }
    }
    return false;
}
bool Date(char str[]) {
    int len = strlen(str);
    if (len == 5) {
        if (isdigit(str[0]) && isdigit(str[1]) && str[2] == '-' && isdigit(str[3]) && isdigit(str[4])) {
            return true;
        }
    }
    return false;
}
bool Time(char str[]) {
    int len = strlen(str);
    if (len == 3 || len == 4) {
        if (len == 3) {
            if (isdigit(str[0]) && (str[1] == 'a' || str[1] == 'p') && str[2] == 'm') {
                return true;
            }
        }
        else if (len == 4) {
            if (str[0] != '0') {
                if (isdigit(str[0]) && isdigit(str[1]) && (str[2] == 'a' || str[2] == 'p') && str[3] == 'm') {
                    return true;
                }
            }
        }
    }
    return false;
}
