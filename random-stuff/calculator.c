#include <stdio.h>

int main(void) {
    float x, y;

    printf("x = ");
    scanf("%f", &x);

    printf("y = ");
    scanf("%f", &y);

    printf("%f + %f = %f\n", x, y, x + y);

}