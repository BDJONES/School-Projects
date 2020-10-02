#include <stdio.h>

int main() {
int num20, num10, num5, num1;
// User prompted to list the amounts of dollar biils

printf("Enter the number of $20s you have: ");
scanf("%d", &num20);
printf("\n");
printf("Enter the number of $10s you have: ");
scanf("%d", &num10);
printf("\n");
printf("Enter the number of $5s you have: ");
scanf("%d", &num5);
printf("\n");
printf("Enter the number of $1s you have: ");
scanf("%d", &num1);
printf("\n");
// How much you have
int totalCash;
totalCash = ((20 * num20) + (10 * num10) + (5 * num5) + (1 * num1));
printf("You have $%d in total cash.\n", totalCash);
// calc the height of coins 
// print the results in INCHES
double coinHeight = 0.0787402;
double height20 = 20 * coinHeight * num20;
double height10 = 10 * coinHeight * num10;
double height5 = 5 * coinHeight * num5;
double height1 = coinHeight * num1;
double totalHeight = height20 + height10 + height5 + height1;

printf("Your stack of coins is %.2lf inches high.\n", totalHeight);
//calc the weight of coins (GRAMS TO POUNDS CALCULATIONS)
// print the results in POUNDS 
double coinWeight = 0.017857422;
double weight20 = 20 * coinWeight * num20;
double weight10 = 10 * coinWeight * num10;
double weight5 = 5 * coinWeight * num5;
double weight1 = coinWeight * num1;
double totalWeight = weight20 + weight10 + weight5 + weight1;
printf("Your stack of coins weighs %.2lf pounds.\n", totalWeight);   

return 0;
}