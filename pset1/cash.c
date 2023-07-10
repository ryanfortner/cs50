#include <stdio.h>

int getQuarters(int cents) {
    int quarters = 0;
    
    while (cents >= 25) {
        quarters++;
        cents = cents - 25;
    }

    return quarters;
}

int getDimes(int cents) {
    int dimes = 0;

    while (cents >= 10) {
        dimes++;
        cents = cents - 10;
    }

    return dimes;
}

int getNickels(int cents) {
    int nickels = 0;

    while (cents >= 5) {
        nickels++;
        cents = cents - 5;
    }

    return nickels;
}

int main(void) {
    int cents = 0;
    while (cents < 1) {
        printf("Change owed: ");
        scanf("%i", &cents);

        if (cents == 0) {
            break;
        }
    }

    int totalQuarters = getQuarters(cents);
    cents = cents - (totalQuarters * 25);

    int totalDimes = getDimes(cents);
    cents = cents - (totalDimes * 10);

    int totalNickels = getNickels(cents);
    cents = cents - (totalNickels * 5);

    int totalPennies = cents;

    printf("Quarters: %i\n", totalQuarters);
    printf("Dimes:    %i\n", totalDimes);
    printf("Nickels:  %i\n", totalNickels);
    printf("Pennies:  %i\n", totalPennies);

    printf("Total Coins Needed: %i\n", totalQuarters + totalDimes + totalNickels + totalPennies);
    return 0;
}