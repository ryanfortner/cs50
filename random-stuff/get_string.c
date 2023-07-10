#include <stdio.h>
#include <string.h>

int main(void) {
    char s[100];
    printf("Input: ");
    scanf(" %[^\n]", s);

    printf("Output: ");
    for(int i = 0; i < strlen(s); i++) {
        printf("%c", s[i]);
    }
    printf("\n");
}