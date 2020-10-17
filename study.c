#include <stdio.h>
#include <string.h>
                                // This program ask the user a series of questions, and determines whether they should take a break or study for an upcoming assignment
int main() {
                                
    char userInput[50];

    printf("What are you worried about (test or project)?\n");
    scanf("%s", userInput);
    
    if (strcmp(userInput, "test") == 0){
        printf("How big a test is it (midterm or quiz)?\n");
        scanf("%s", userInput);
        
        if(strcmp(userInput, "midterm") == 0){
            printf("A major class?\n");
            scanf("%s", userInput);
            
            if (strcmp(userInput, "yes") == 0) {
                printf("Required Class?\n");
                scanf("%s", userInput);
                
                if (strcmp(userInput, "yes") == 0) {
                    printf("Taken it before?\n");
                    scanf("%s",userInput);

                    if (strcmp(userInput, "no") == 0) {
                        printf("Are you ready?\n");
                        scanf("%s", userInput);

                        if (strcmp(userInput, "yes") == 0) {
                            printf("Do something fun!\n");
                        }
                        else if (strcmp(userInput, "no") == 0) {
                            printf("You need to study!\n");
                        }
                    }
                    else if (strcmp(userInput, "yes") == 0) {
                        printf("You need to study!");
                    }

                }
                else if (strcmp(userInput, "no") == 0){
                    printf("Doing well?\n");
                    scanf("%s", userInput);

                    if (strcmp(userInput, "yes") == 0) {
                        printf("Do something fun!\n");
                    }
                    else if (strcmp(userInput, "no") == 0) {
                        printf("You need to study!\n");
                    }

                }
            }
            else if(strcmp(userInput, "no") == 0) {
                printf("Easy class?\n");
                scanf("%s", userInput);
                
                if (strcmp(userInput, "yes") == 0) {
                    printf("Do something fun!\n");
                }
                else if (strcmp(userInput, "no") == 0) {
                    printf("You need to study!\n");
                }
            }

        }
        else if (strcmp(userInput, "quiz") == 0){
            printf("Pass the last quiz?\n");
            scanf("%s", userInput);

            if (strcmp(userInput, "yes") == 0) {
                printf("Pass easily?\n");
                scanf("%s", userInput);

                if (strcmp(userInput, "yes") == 0) {
                    printf("Do something fun!\n");
                }
                else if (strcmp(userInput, "no") == 0) {
                    printf("You need to study!\n");
                }
            }
            else if (strcmp(userInput, "no") == 0) {
                    printf("You need to study!\n");
                }
        }
    }
    else if (strcmp(userInput, "project") == 0){
        printf("What kind (huge or normal or extra-credit)?\n");
        scanf("%s", userInput);
        
        if (strcmp(userInput, "huge") == 0) {
            printf("Due soon (tomorrow or this-week or next-week)?\n");
            scanf("%s", userInput);

            if (strcmp(userInput, "tomorrow") == 0) {
                printf("You need to study!\n");
            }
            else if (strcmp(userInput, "this-week") == 0) {
                printf("Almost finished?\n");
                scanf("%s", userInput);
                
                if (strcmp(userInput, "yes") == 0) {
                    printf("Do something fun!\n");
                }  
                else if (strcmp(userInput, "no") == 0) {
                        printf("Have you started?\n");
                        scanf("%s", userInput);

                        if (strcmp(userInput, "yes") == 0) {
                            printf("Do something fun!\n");
                        }
                        else if (strcmp(userInput, "no") == 0) {
                            printf("You need to study!\n");
                        }
                }
            }
            else if (strcmp(userInput, "next-week") == 0){
                printf("Busy weekend?\n");
                scanf("%s", userInput);

                if (strcmp(userInput, "yes") == 0) {
                    printf("You need to study!\n");
                }
                else if (strcmp(userInput, "no") == 0) {
                    printf("Do something fun!\n");
                }
            }
        }
        else if (strcmp(userInput, "normal") == 0) {
            printf("Can you drop one?\n");
            scanf("%s", userInput);

            if (strcmp(userInput, "yes") == 0) {
                printf("Already dropped 1?\n");
                scanf("%s", userInput);

                if (strcmp(userInput, "yes") == 0) {
                    printf("You need to study!\n");
                }
                else if (strcmp(userInput, "no") == 0) {
                    printf("Do something fun!\n");
                }
            }
            else if (strcmp(userInput, "no") == 0) {
                printf("You need to study!\n");
            }
        }
        else if (strcmp(userInput, "extra-credit") == 0) {
            printf("Course grade(great or not-great)?\n");
            scanf("%s", userInput);

            if (strcmp(userInput, "great") == 0){
                printf("Do something fun!\n");
            }
            else if (strcmp(userInput, "not-great") == 0) {
                printf("You need to study!\n");
            }
        }

    }
    return 0;

}
