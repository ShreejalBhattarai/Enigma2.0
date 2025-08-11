#include <stdio.h>
#include <ctype.h>
#include "plugboard.h"

#define ALPHABET_SIZE 26

int plugboard_mapping[ALPHABET_SIZE];

void reset_plugboard() {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        plugboard_mapping[i] = i;
    }
}

void set_plugboard() {
    char letterone, lettertwo;
    printf("Please input the two letters that you want to swap (e.g., A F):\n");
    scanf(" %c %c", &letterone, &lettertwo);
    letterone = toupper(letterone);
    lettertwo = toupper(lettertwo);

    int idx1 = letterone - 'A';
    int idx2 = lettertwo - 'A';

    if (idx1 >= 0 && idx1 < ALPHABET_SIZE && idx2 >= 0 && idx2 < ALPHABET_SIZE) {
        int temp = plugboard_mapping[idx1];
        plugboard_mapping[idx1] = plugboard_mapping[idx2];
        plugboard_mapping[idx2] = temp;
        printf("Plugboard mapping updated: %c <-> %c\n", letterone, lettertwo);
    } else {
        printf("Invalid letters entered!\n");
    }

    // Flush stdin after scanf
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

char plugboard_get_mapping(int index) {
    return 'A' + plugboard_mapping[index];
}

void apply_plugboard_mapping(char *message) {
    for (int i = 0; message[i] != '\0'; i++) {
        if (isalpha(message[i])) {
            int idx = toupper(message[i]) - 'A';
            message[i] = plugboard_get_mapping(idx);
        }
    }
}
