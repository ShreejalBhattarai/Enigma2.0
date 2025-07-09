#include "pico/stdlib.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "functions.h"

// ───── ROTOR MODULE ─────

void reset_rotors(void) {
    printf("[Rotor] Rotors reset to initial positions.\n");
}

void step_rotors(void) {
    // Placeholder rotor stepping
    static int counter = 0;
    counter++;
    printf("[Rotor] Stepped rotors (step %d)\n", counter);
}

char enigma_encrypt(char ch) {
    // Very simple mock: rotate letter forward by 1
    if (!isalpha(ch)) return ch;
    ch = toupper(ch);
    return (ch - 'A' + 1) % 26 + 'A';
}

// ───── PLUGBOARD MODULE ─────

void set_plugboard(void) {
    printf("[Plugboard] Set plugboard pairs (mock).\n");
}

void apply_plugboard_mapping(char *ch) {
    // Example: A↔M, B↔N, C↔O
    if (!isalpha(*ch)) return;

    switch (toupper(*ch)) {
        case 'A': *ch = 'M'; break;
        case 'M': *ch = 'A'; break;
        case 'B': *ch = 'N'; break;
        case 'N': *ch = 'B'; break;
        case 'C': *ch = 'O'; break;
        case 'O': *ch = 'C'; break;
        default: break;
    }
}

void reverse_plugboard_mapping(char *ch) {
    // Plugboard is symmetric in Enigma
    apply_plugboard_mapping(ch);
}

void reset_plugboard(void) {
    printf("[Plugboard] Plugboard mappings cleared.\n");
}

// ───── LED MODULE ─────

void setup_leds(void) {
    // Set GPIOs for A–Z (0–25)
    for (int i = 0; i < 26; ++i) {
        gpio_init(i);
        gpio_set_dir(i, GPIO_OUT);
    }
    printf("[LED] 26 GPIOs initialized for A–Z LEDs.\n");
}

void blink_led_for_letter(char ch) {
    if (!isalpha(ch)) return;
    int pin = toupper(ch) - 'A';

    if (pin < 0 || pin > 25) return;

    // Turn off all LEDs first
    for (int i = 0; i < 26; ++i) {
        gpio_put(i, 0);
    }

    // Blink the current letter's LED
    gpio_put(pin, 1);
    sleep_ms(300); // short blink
    gpio_put(pin, 0);
    printf("[LED] Blinking LED for '%c' (GPIO %d)\n", ch, pin);
}

// ───── CONFIG MODULE ─────

void load_config(void) {
    printf("[Config] Loaded config (mock).\n");
}

void save_config(void) {
    printf("[Config] Saved config (mock).\n");
}

// ───── UI UTILITIES ─────

bool confirm(const char *prompt) {
    char c;
    printf("%s", prompt);
    scanf(" %c", &c);
    return (c == 'y' || c == 'Y');
}
