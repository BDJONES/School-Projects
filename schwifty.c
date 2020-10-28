#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
                                // This program is meant to change the way a set of words is printed out, changing the order and which characters appear
void left(char word[]);         // This function causes the characters in a string to shift to the left one position (such as 'hello' -> 'elloh')
void right(char word[]);        // This function causes the characters in a string to shift to the right one position (such as 'hello' -> 'ohell')
void inc(char word[]);          // This function causes all characters in the string to increase to the next ASCII value (such as 'a' -> 'b') 
void dec(char word[]);          // This function causes all characters in the string to decrease to the next ASCII value (such as 'b' -> 'a')

int main(int argc, char* argv[]) {
    char word[100];
    bool off = true;
    if (argc != 3) {
        printf("Invalid number of arguments");
        return 1;
    }
    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        printf("Could not open file '%s'", argv[1]);
        return 1;
    }
    while(1){
        fscanf(fp, "%s ", word);
        char args[100];
        strcpy(args, argv[2]);
        int size = strlen(args);
        for (int i = 0; i < size; ++i) {
            if (args[i] == 'L') {
                left(word);
            }
            else if (args[i] == 'R') {
                right(word);
            }
            else if (args[i] == 'I') {
                inc(word);
            }
            else if (args[i] == 'D') {
                dec(word);
            }
            else {
                off = false;
                printf("You threw off my schwiftiness with schwifty '%c'!\n", args[i]);
                return 1;
            }
        }
        if (off == true) {
            fprintf(stdout,"%s\n", word);
        }
        if (feof(fp)) {
            break;
        }
        
    }
    fclose(fp);
    return 0;
}
void left(char word[]) {
    char temp = word[0];
    for (int i = 0, size = strlen(word); i < size; ++i) {
        if (i == (size - 1)) {
            word[size - 1] = temp; 
        }
        else {
            word[i] = word[i + 1];
        }
    }
}

void right(char word[]){
    int size = strlen(word);
    char temp = word[size - 1];
    for (int i = (size - 1); i >= 0; --i) {
        if (i == 0) {
            word[0] = temp; 
        }
        else {
            word[i] = word[i - 1];
        }
    }
}
void inc(char word[]) {
    int len = strlen(word);
    for (int i = 0; i < len; ++i) {
        char check = word[i];
        if (isalpha(check)) {
            if (check == 'Z') { // relaps into 'A' or 'a' or '0' if the character is 'Z' or 'z' or '9' respectively 
                check = 'A';
            }
            else if (check == 'z') {
                check = 'a';    
            }
            else {
                ++check;
            }
        }
        else if (isdigit(check)) {
            if (check == '9') {
                check = '0';
            }
            else {
                ++check;
            }
        }
        word[i] = check;
    }
}
void dec(char word[]) {
    int len = strlen(word);
    for (int i = 0; i < len; ++i) { // Does the same as the increase function but in reverse ('A' -> 'Z' or 'a' -> 'z' or '0' -> '9')
        char check = word[i];
        if (isalpha(check)) {
            if (check == 'A') {
                check = 'Z';
            }
            else if (check == 'a') {
                check = 'z';    
            }
            else {
                --check;
            }
        }
        else if (isdigit(check)) {
            if (check == '0') {
                check = '9';
            }
            else {
                --check;
            }
        }
        word[i] = check;
    }
}
