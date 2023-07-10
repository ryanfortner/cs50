#include <stdio.h>

float final(float price, float discount);

int main(void) {
    float price, discount;

    printf("What is the original price? ");
    scanf("%f", &price);

    printf("What is the percent discount? " );
    scanf("%f", &discount);

    float sale = final(price, discount);

    printf("Sale Price: %.2f\n", sale);
}

float final(float price, float discount) {
    return price * ((100 - discount) / 100);
}