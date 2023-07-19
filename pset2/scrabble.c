#include <stdio.h>
#include <string.h>
#include <ctype.h>

int points[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int computeScore(char* word) {
    int score = 0;

    for (int i = 0, l = strlen(word); i < l; i++) {
        if (isupper(word[i])) {
            score += points[word[i] - 'A'];
        } else if (islower(word[i])) {
            score += points[word[i] - 'a'];
        }
    }

    return score;
}

int main(void) {
    char word1[256];
    char word2[256];

    // ask user for words
    printf("Player 1: ");
    fgets(word1, 256, stdin);
    printf("Player 2: ");
    fgets(word2, 256, stdin);

    // compute scores
    int p1Score = computeScore(word1);
    int p2Score = computeScore(word2);

    // print results
    if (p1Score > p2Score) {
        printf("Player 1 wins!\n");
    } else if (p1Score < p2Score) {
        printf("Player 2 wins!\n");
    } else if (p1Score == p2Score) {
        printf("Tie!\n");
    }

    return 0;
}