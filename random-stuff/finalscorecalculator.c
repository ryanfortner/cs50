// 06.28.23
// Calculate target final exam grade from quarters
// Assumes exam is weighted 20% 

#include <stdio.h>

float findQuarterlyAverage(int QuarterCount, float quarterScores[]);

float sum = 0;
float QuarterlyAverage;

int main(void) {

    int i, QuarterCount, finalExamWeight;

    // calculate average
    printf("[?] How many quarter grades would you like to average? ");
    scanf("%i", &QuarterCount);
    float quarterScores[QuarterCount];
    float testVar = findQuarterlyAverage(QuarterCount, quarterScores);
    printf("[*] Average of %i quarters before final is %.3f\n", QuarterCount, testVar);

    float GoalA, GoalB, GoalC, GoalD;

    GoalA = (5 * 90) - (4 * testVar);
    GoalB = (5 * 80) - (4 * testVar);
    GoalC = (5 * 70) - (4 * testVar);
    GoalD = (5 * 60) - (4 * testVar);

    // print everything
    printf("\n");
    printf("To get an A\tTo get a B\tTo get a C\tTo get a D\n");
    printf("%.3f       \t%.3f      \t%.3f      \t%.3f      \n", GoalA, GoalB, GoalC, GoalD);
}

float findQuarterlyAverage(int QuarterCount, float quarterScores[]) {

    // get user's scores
    for (int i = 0; i < QuarterCount; i++) {
        printf("    [?] Enter quarter %i score: ", i + 1);
        scanf("%f", &quarterScores[i]);
    }

    // find total of all values in the array
    for (int i = (QuarterCount - 1); i >=0; i--) {
        sum = sum + quarterScores[i];
    }

    // find the actual average
    float QuarterlyAverage = sum / (int)QuarterCount;
    
    return QuarterlyAverage;
}
