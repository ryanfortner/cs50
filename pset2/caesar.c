#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

static char *encryptPlaintext(int key, char plaintext[]) { // rotate ascii values by specified key    
    static char ciphertext[256];
    for (int i = 0, l = strlen(plaintext); i < l; i++) {
        if (isalpha(plaintext[i])) {
            if (isupper(plaintext[i])) {
                ciphertext[i] = (((plaintext[i] - 'A') + key) % 26) + 'A';
            } else if (islower(plaintext[i])) {
                ciphertext[i] = (((plaintext[i] - 'a') + key) % 26) + 'a';
            }
        } else {
            ciphertext[i] = plaintext[i];
        }
    }

    return ciphertext;
}

int main(int argc, char **argv) {
    // get key
    int key;
    if (argc < 2 || argc > 2) {
        printf("Usage: ./caesar key\n");
        return 0;
    } else if (argc == 2) {
        char *arg = argv[1];
        while (*arg) {
            if (!isdigit(*arg)) { // make sure input is a digit
                fprintf(stderr, "Error: argument '%s' is not a number.\n", arg);
                return 1;
            }
            arg++;
        }
        key = atoi(argv[1]);
    }

    // get plaintext
    char plaintext[256];
    printf("Plaintext: ");
    fgets(plaintext, 256, stdin);

    // get and print ciphertext
    printf("Ciphertext: %s\n", encryptPlaintext(key, plaintext));

    return 0;
}