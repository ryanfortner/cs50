#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/*
TODO:
- encode plaintext (preserve case)
- return ciphertext
*/

bool hasRepeatedCharacters(const char* str) {
    bool characters[256] = { false };

    while (*str != '\0') {
        unsigned char currentChar = (unsigned char)*str;
        if (islower(currentChar)) {
            currentChar = toupper(currentChar);
        }
        if (characters[currentChar]) {
            return true; // repeated character found
        }
        characters[currentChar] = true;
        str++;
    }

    return false; // no repeated characters found
}

static char *getPlaintext(void) {
    static char plaintext[256];
    printf("Plaintext: ");
    fgets(plaintext, 256, stdin);

    return plaintext;
}

static char *encodePlaintext(char *key, char *plaintext) {
    size_t length = strlen(plaintext);
    char *ciphertext = (char*)malloc((length + 1) * sizeof(char));
    int index;

    if (ciphertext == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < length; i++) {
        if (islower(plaintext[i])) {
            index = plaintext[i] - 'a';
            ciphertext[i] = key[index];
            if (isupper(ciphertext[i])) {
                ciphertext[i] += 32;
            }
        }
        else if (isupper(plaintext[i])) {
            index = plaintext[i] - 'A';
            ciphertext[i] = key[index];
            if (islower(ciphertext[i])) {
                ciphertext[i] -= 32;
            }
        }
        else {
            // Preserve non-alphabetic characters in the ciphertext
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[length] = '\0';

    return ciphertext;
}

int main(int argc, char **argv) {
    char *key = argv[1];
    
    // get key
    if (argc != 2) {
        fprintf(stderr, "Usage: ./substitution KEY\n");
        return 1;
    }
    if (strlen(argv[1]) != 26) { // make sure length of 26
        fprintf(stderr, "Error: key is not 26 characters in length.\n");
        return 1;
    }
    if (hasRepeatedCharacters(key)) {
        fprintf(stderr, "Error: key contains repeated characters.\n");
        return 1;
    }
    while (*key != '\0') { 
        if (!isalpha(*key)) { // check for any non-alphabetic characters
            fprintf(stderr, "Error: given key contains at least one non-alphabetic character.\n");
            return 1;
        }
        key++;
    }
    key = argv[1]; // reset pointer back to the start
    
    // get plaintext
    char *plaintext = getPlaintext();

    // encode plaintext
    char *ciphertext = encodePlaintext(key, plaintext);
    
    printf("%s\n", ciphertext);

    free(ciphertext);
    return 0;
}