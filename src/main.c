#include "pico/stdlib.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <functions.cpp>

#define MAX_MESSAGE_LENGTH 512

// --- External functions ---
void reset_rotors();
void step_rotors();
char enigma_encrypt(char ch);
void apply_plugboard_mapping(char *ch);
void reverse_plugboard_mapping(char *ch);
void setup_leds();
void blink_led_for_letter(char ch);
void load_config();
void save_config();
void set_plugboard();
void set_rotor_order();
void set_ring_settings();
void reset_plugboard();
bool confirm(const char *prompt);

// --- UI Helpers ---
void print_banner() {
    printf("\n");
    printf("╔═════════════════════════════════════════════════════════╗\n");
    printf("║                   ENIGMA 2.0                            ║\n");
    printf("║   Electronic Replica of the original cipher machine.    ║\n");
    printf("╚═════════════════════════════════════════════════════════╝\n");
}

void print_menu() {
    printf("\nMain Menu:\n");
    printf("  [E] Encrypt Message\n");
    printf("  [D] Decrypt Message\n");
    printf("  [C] Configure Machine\n");
    printf("  [L] Load Config\n");
    printf("  [S] Save Config\n");
    printf("  [R] Reset All Settings\n");
    printf("  [Q] Quit\n");
}

char get_menu_choice() {
    char choice;
    printf("Select option: ");
    scanf(" %c", &choice);
    return toupper(choice);
}

void clean_input(char *in, char *out) {
    int j = 0;
    for (int i = 0; in[i] != '\0' && j < MAX_MESSAGE_LENGTH - 1; i++) {
        if (isalpha(in[i])) {
            out[j++] = toupper(in[i]);
        }
    }
    out[j] = '\0';
}

void process_message(const char *message) {
    for (int i = 0; message[i] != '\0'; i++) {
        char ch = message[i];

        apply_plugboard_mapping(&ch);
        char enc = enigma_encrypt(ch);
        reverse_plugboard_mapping(&enc);

        printf("%c", enc);
        blink_led_for_letter(enc);

        step_rotors();
    }
    printf("\n");
}

// --- Main Entry ---
int main() {
    stdio_init_all();
    sleep_ms(2000); // Give USB serial time

    setup_leds();
    reset_rotors();
    reset_plugboard();

    print_banner();

    char input_raw[MAX_MESSAGE_LENGTH];
    char input_clean[MAX_MESSAGE_LENGTH];

    while (true) {
        print_menu();
        char choice = get_menu_choice();

        switch (choice) {
            case 'E':
            case 'D':
                reset_rotors(); // Same behavior for symmetric enc/dec
                printf("Enter your message: ");
                scanf(" %[^\n]s", input_raw);

                clean_input(input_raw, input_clean);

                if (strlen(input_clean) == 0) {
                    printf("No valid letters to process.\n");
                    break;
                }

                printf("Output: ");
                process_message(input_clean);
                break;

            case 'C': {
                char c;
                do {
                    printf("\n[1] Set Plugboard\n");
                    printf("[2] Set Rotor Order\n");
                    printf("[3] Set Ring Settings\n");
                    printf("[4] Back\n");
                    printf("Choose: ");
                    scanf(" %c", &c);

                    switch (c) {
                        case '1': set_plugboard(); break;
                        case '2': set_rotor_order(); break;
                        case '3': set_ring_settings(); break;
                        case '4': break;
                        default: printf("Invalid option.\n");
                    }
                } while (c != '4');
                break;
            }

            case 'L':
                if (confirm("Load config from flash? (y/n): ")) {
                    load_config();
                    printf("Config loaded.\n");
                }
                break;

            case 'S':
                if (confirm("Save current config to flash? (y/n): ")) {
                    save_config();
                    printf("Config saved.\n");
                }
                break;

            case 'R':
                if (confirm("Reset all settings to defaults? (y/n): ")) {
                    reset_rotors();
                    reset_plugboard();
                    printf("All settings reset.\n");
                }
                break;

            case 'Q':
                printf("Exiting. Goodbye!\n");
                return 0;

            default:
                printf("Invalid selection. Try again.\n");
        }
    }

    return 0;
}
