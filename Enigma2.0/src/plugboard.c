#include <stdio.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

// Global plugboard mapping
int plugboard_mapping[ALPHABET_SIZE];

// Reset to default (A→A, B→B, etc.)
void reset_plugboard() {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        plugboard_mapping[i] = i;
    }
}

void set_plugboard() {
    char letterone, lettertwo;

    printf("Please input the two letters that you want to swap (e.g., A F):\n");
    scanf(" %c %c", &letterone, &lettertwo);

    // Convert to uppercase and indexes
    letterone = toupper(letterone);
    lettertwo = toupper(lettertwo);
    int idx1 = letterone - 'A';
    int idx2 = lettertwo - 'A';

    if (idx1 >= 0 && idx1 < ALPHABET_SIZE && idx2 >= 0 && idx2 < ALPHABET_SIZE) {
        // Swap mappings
        int temp = plugboard_mapping[idx1];
        plugboard_mapping[idx1] = plugboard_mapping[idx2];
        plugboard_mapping[idx2] = temp;
        printf("Plugboard mapping updated: %c <-> %c\n", letterone, lettertwo);
    } else {
        printf("Invalid letters entered!\n");
    }
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
