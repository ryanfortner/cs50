#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>

int countLetters(char *inputText) {
    int counter = 0;
    for (int i = 0, l = strlen(inputText); i < l; i++) {
        if (isalpha(inputText[i])) {
            counter++;
        }
    }
    return counter;
}

int countWords(char *inputText) {
    int counter = 0;
    bool isWord = false;

    for (int i = 0, l = strlen(inputText); i < l; i++) {
        if (inputText[i] != ' ' && inputText[i] != '\t' && inputText[i] != '\n' && inputText[i] != '\r') {
            if (!isWord) {
                isWord = true;
                counter++;
            }
        } else { // current character is whitespace, start new word
            isWord = false;
        }
    }

    return counter;
}

int countSentences(char *inputText) {
    int counter = 0;

    for(int i = 0, l = strlen(inputText); i < l; i++) {
        if (inputText[i] == '!' || inputText[i] == '?' || inputText[i] == '.') {
            counter++;
        }
    }

    return counter;
}

int main(void) {
    char inputText[256];

    printf("Enter text: ");
    fgets(inputText, 256, stdin);

    printf("%i letters, %i words, %i sentences\n", countLetters(inputText), countWords(inputText), countSentences(inputText));

    int l = countLetters(inputText);
    int w = countWords(inputText);
    int s = countSentences(inputText);

    int gradeLevel = round(0.0588 * (l / ((float)w / 100)) - 0.296 * (s / ((float)w / 100)) - 15.8);

    if (gradeLevel >= 16) {
        printf("Grade 16+\n");
    } else if (gradeLevel < 1) {
        printf("Before Grade 1\n");
    } else {
        printf("Grade %i\n", gradeLevel);
    }
}