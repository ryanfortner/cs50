#include <stdio.h>

int main(void) {
    printf("Enter an int: ");
    int a, b;
    scanf("%i", &a);

    printf("Enter another int: ");
    scanf("%i", &b);

    if (a == b) {
        printf("Equal\n");
    }
    else {
        printf("Not equal\n");
    }
}