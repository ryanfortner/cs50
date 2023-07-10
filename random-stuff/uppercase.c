#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    char s[100];
    printf("Before: ");
    scanf(" %[^\n]", s);

    for(int i = 0, n = strlen(s); i < n; i++) {
        if(islower(s[i])) {
            printf("%c", toupper(s[i]));
        }
        else {
            printf("%c", s[i]);
        }
    }
    printf("\nDone!\n");
}