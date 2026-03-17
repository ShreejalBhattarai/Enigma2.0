#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "pico/stdlib.h"
#include "functions.h"
#include "plugboard.h"
#include "rotors.h"
#include "ui_functions.h"

#define MAX_MESSAGE_LENGTH 512
#define INPUT_BUFFER_SIZE 64

void clean_input(const char *input_raw, char *input_clean) {
    int j = 0;
    for (int i = 0; input_raw[i] != '\0'; i++) {
        if (isalpha((unsigned char)input_raw[i])) {
            input_clean[j++] = toupper((unsigned char)input_raw[i]);
        }
    }
    input_clean[j] = '\0';
}

void clear_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

char encode_char(char c) {
    if (c < 'A' || c > 'Z') return c;
    int letter = c - 'A';

    rotors_step();

    letter = plugboard_get_mapping(letter) - 'A';

    for (int i = 0; i < 3; i++) {
        letter = rotor_forward(letter, i);
    }

    letter = reflector_reflect(letter);

    for (int i = 2; i >= 0; i--) {
        letter = rotor_backward(letter, i);
    }

    letter = plugboard_get_mapping(letter) - 'A';

    return (char)(letter + 'A');
}

void process_message(char *message) {
    for (int i = 0; message[i] != '\0'; i++) {
        message[i] = encode_char(message[i]);
    }
    printf("%s\n", message);
}

char get_menu_choice() {
    int c;

    // Read the first non-whitespace character (doesn't require Enter in most serial terminals).
    while ((c = getchar()) != EOF) {
        if (c == '\n' || c == '\r' || c == ' ' || c == '\t') {
            continue;
        }

        // Drain any remaining buffered characters without blocking.
        // Some serial monitors send a full line (ending with '\n'), others send single chars.
        while (true) {
            int d = getchar_timeout_us(0);
            if (d == PICO_ERROR_TIMEOUT) break;
            if (d == '\n' || d == '\r') break;
        }

        return toupper((unsigned char)c);
    }

    return '\0';
}

int confirm(char c) {
    return (c == 'y' || c == 'Y');
}

void reset_rotors() {
    rotors_init();
    printf("Rotors reset to default position.\n");
}

void setup_leds() {
    printf("LEDs setup complete.\n");
}

void set_rotor_order(int a, int b, int c) {
    rotors_set_order(a, b, c);
    printf("Rotor order set to: %d %d %d\n", a, b, c);
}

void set_ring_settings(int r1, int r2, int r3) {
    rotors_set_ring_settings(r1, r2, r3);
    printf("Ring settings set to: %d %d %d\n", r1, r2, r3);
}

void load_config() {
    printf("Loaded configuration from storage (stub).\n");
}

void save_config() {
    printf("Saved configuration to storage (stub).\n");
}

int mod26(int x) {
    return (x % 26 + 26) % 26;
}
