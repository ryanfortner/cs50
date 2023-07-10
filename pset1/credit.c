#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int containsLetters(const char *str) {
    while (*str) {
        if (isalpha(*str)) {
            return 1; // contains at least 1 letter
        }
        str++;
    }
    return 0; // doesn't contain letters
}

int checkLuhn(const char *num) { // check against Luhn's algorithm, 1 valid, 0 invalid
    // take string, convert to long.
    long long numLong = strtol(num, NULL, 10);
    int sum1 = 0;
    int sum2 = 0;
    int total = 0;
    int mod1, mod2;
    int d1, d2;

    while (numLong > 0) {
        // remove last digit, add to sum1
        mod1 = numLong % 10;
        numLong = numLong / 10;
        sum1 = sum1 + mod1;

        // remove second to last digit
        mod2 = numLong % 10;
        numLong = numLong / 10;

        // double second to last digit, add digits to sum2
        mod2 = mod2 * 2;
        d1 = mod2 % 10;
        d2 = mod2 / 10;
        sum2 = sum2 + d1 + d2;
    }

    total = sum1 + sum2;

    if (total % 10 != 0) {
        return 0;
    }
    return 1;
}

int main(void) {
    char num[256];

    int AMEX = 0;
    int MASTERCARD = 0;
    int VISA = 0;

    // ask user for credit card num, in string form.
    printf("Enter your card num: ");
    fgets(num, 256, stdin);
    
    // check whether it's a valid num
    if ((strlen(num) - 1) < 13 || (strlen(num) - 1) > 16 || containsLetters(num)) {
        fprintf(stderr, "INVALID\n");
        return 1;
    }

    if (checkLuhn(num) == 0) {
        fprintf(stderr, "INVALID\n");
        return 1;
    }

    switch (num[0]) {
        case '3': // amex
            if (num[1] == '4' || num[1] == '7') {
                if ((strlen(num) - 1) == 15) {
                    AMEX = 1;
                    break;
                }
                fprintf(stderr, "INVALID\n");
                return 1;
                break;
            }
            fprintf(stderr, "INVALID\n");
            return 1;
            break;
        case '4': // visa
            if ((strlen(num) - 1) == 13 || (strlen(num) - 1) == 16) {
                VISA = 1;
                break;
            }
            fprintf(stderr, "INVALID\n");
            return 1;
            break;
        case '5': // master
            switch (num[1]){
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                    if ((strlen(num) - 1) == 16) {
                        MASTERCARD = 1;
                        break;
                    }
                    fprintf(stderr, "INVALID\n");
                    return 1;
                    break;
                default:
                    fprintf(stderr, "INVALID\n");
                    return 1;
            }
            break;        
        default:
            fprintf(stderr, "INVALID\n");
            return 1;
    }

    if (VISA == 1) {
        printf("VISA\n");
    } else if (MASTERCARD == 1) {
        printf("MASTERCARD\n");
    } else if (AMEX == 1) {
        printf("AMEX\n");
    }
    return 0;
}