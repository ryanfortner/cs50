#include <stdio.h>

int main(void) {
    char name[256];
    printf("Name: ");
    fgets(name, 256, stdin);

    printf("Hello, %s\n", name);
    return 0;
}