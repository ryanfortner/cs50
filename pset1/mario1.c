#include <stdio.h>

void printRow(int bricks, int spaces)
{
    for (int j = 0; j < spaces; j++) {
        printf(" ");
    }
    for (int i = 0; i < bricks; i++) {
        printf("#");
    }
    printf("\n");
}

int main(void) {
    int n;
    do {
        printf("Enter a number: ");
        scanf("%i", &n);
    } while(n < 1 || n > 8);

    for (int i = 0; i < n; i++) {
        printRow(i + 1, n - i);
    }
}