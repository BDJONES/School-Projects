#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

void left(char word[]);
void right(char word[]);
void inc(char word[]);
void dec(char word[]);

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
            if (check == 'Z') {
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
    for (int i = 0; i < len; ++i) {
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
