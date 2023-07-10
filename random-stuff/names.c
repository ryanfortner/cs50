#include <stdio.h>
#include <string.h>

int main(void) {
    char *names[] = {"Bob", "Charlie", "Fred", "George"};
    for(int i = 0; i < 4; i++) {
        printf("%s\n", names[i]);
        if(strcmp(names[i], "George") == 0) {
            printf("Found\n");
            return 0;
        }
    }
    return 1;
}