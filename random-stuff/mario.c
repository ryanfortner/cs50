#include <stdio.h>

int main(void) {
    int n;

    do {
        scanf("%i", n);
    }
    while (n < 1);

    for (int i; i < n; i++) {
        printf("#\n");
    }
}