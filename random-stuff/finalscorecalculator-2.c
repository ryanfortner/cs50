#include <stdio.h>

int main(int argc, float **argv) {
    if(argc == 1) {
        printf("No arguments given\n");
        return 1;
    }

    // add up all user-inputted scores
    float quarterSum;
    for(int i = 1; i <= (argc - 1); i++) {
        quarterSum = quarterSum + *argv[i];
    }

    // find the average
    float quarterAverage = quarterSum / (argc - 1);
    printf("%f\n", quarterAverage);
    return 0;
}