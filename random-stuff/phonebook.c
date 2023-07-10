#include <stdio.h>
#include <string.h>

typedef struct {
    char *name;
    char *number;
}
person;

int main(void) {
    person people[2];

    people[0].name = "Carter";
    people[0].number = "+1-617-495-1000";

    people[1].name = "David";
    people[1].number = "+1-949-218-1991";

    for(int i = 0; i < 2; i++) {
        if(!strcmp(people[i].name, "David")) {
            printf("Found %s\n", people[i].number);
            return 0;
        }
    }
    printf("Not found\n");
    return 1;
}