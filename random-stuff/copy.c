#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    char s[256];
    printf("Enter a string: ");
    fgets(s, sizeof(s), stdin);

    char *t = malloc(strlen(s) + 1);

    if (t == NULL) {
        return 1;
    }

    strcpy(t, s);
    
    if (strlen(t) > 0) {
        t[0] = toupper(t[0]);

    }

    printf("s: %s\n", s);
    printf("t: %s\n", t);

    free(t);
}