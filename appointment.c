#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

bool Name(char str[]);
bool Building(char str[]);
bool Date(char str[]);
bool Time(char str[]);

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
