#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"
#include "plugboard.h"
#include "ui_functions.h"
#include "pico/stdlib.h"

#define MAX_MESSAGE_LENGTH 512
#define INPUT_BUFFER_SIZE 64
#define SLEEP_TIME_MS 2000

// Flush leftover stdin input
void flush_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Reads a menu choice character robustly


int main() {
    char input_raw[MAX_MESSAGE_LENGTH];
    char input_clean[MAX_MESSAGE_LENGTH];
    char input_buffer[INPUT_BUFFER_SIZE];

    stdio_init_all();
    setvbuf(stdout, NULL, _IONBF, 0);
    sleep_ms(SLEEP_TIME_MS);

    reset_rotors();
    setup_leds();
    reset_plugboard();

    greet_user();
    sleep_ms(SLEEP_TIME_MS);
    print_banners();
    sleep_ms(SLEEP_TIME_MS);

    while (1) {
        print_menu();
        char choice = get_menu_choice();

        if (choice == '\0') {
            printf("No valid input. Please try again.\n");
            continue;
        }

        printf("%c\n", choice);

        switch (choice) {
            case 'E':
            case 'D': {
                reset_rotors();
                printf("Enter your message (Enter to finish): \n");
                fflush(stdout);

                // Read input in a way that works for serial monitors that don't send '\n'
                // until Enter is pressed. If the user pauses for a moment, we treat it as end.
                size_t len = 0;
                const uint32_t idle_timeout_us = 700 * 1000; // 700ms idle ends message if we have chars
                absolute_time_t last_rx = get_absolute_time();

                while (len < sizeof(input_buffer) - 1) {
                    int ch = getchar_timeout_us(0);
                    if (ch == PICO_ERROR_TIMEOUT) {
                        if (len > 0 && absolute_time_diff_us(last_rx, get_absolute_time()) > (int64_t)idle_timeout_us) {
                            break;
                        }
                        tight_loop_contents();
                        continue;
                    }

                    last_rx = get_absolute_time();

                    if (ch == '\n' || ch == '\r') {
                        break;
                    }

                    input_buffer[len++] = (char)ch;
                }
                input_buffer[len] = '\0';

                // Drain any extra characters without blocking (in case user typed too much)
                while (getchar_timeout_us(0) != PICO_ERROR_TIMEOUT) {
                    // keep draining
                }

                // Clean input (only letters, uppercase)
                clean_input(input_buffer, input_clean);

                if (strlen(input_clean) == 0) {
                    printf("No valid letters to process. Please try again with letters.\n");
                    break; // Exit the switch case if no valid letters
                }

                printf("Output: ");
                process_message(input_clean);
                printf("\n\n"); // Added for better output formatting
                break;
            }


            case 'C': {
                char config_choice = '\0';

                do {
                    printf("\n--- Configuration Menu ---\n");
                    printf("[1] Set Plugboard\n");
                    printf("[2] Set Rotor Order\n");
                    printf("[3] Set Ring Settings\n");
                    printf("[4] Back to Main Menu\n");
                    printf("Choose: ");

                    config_choice = get_menu_choice();
                    printf("%c\n", config_choice);

                    switch (config_choice) {
                        case '1':
                            set_plugboard();
                            break;

                        case '2': {
                            int a, b, c;
                            printf("Please Enter the Rotor Order (e.g., 1 2 3): ");

                            if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
                                printf("Input error.\n");
                                break;
                            }

                            if (sscanf(input_buffer, "%d %d %d", &a, &b, &c) == 3) {
                                set_rotor_order(a, b, c);
                            } else {
                                printf("Invalid rotor order input.\n");
                            }
                            break;
                        }

                        case '3': {
                            int r1, r2, r3;
                            printf("Enter ring settings (1-26) for rotors 1 2 3 separated by space: ");

                            if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
                                printf("Input error.\n");
                                break;
                            }

                            if (sscanf(input_buffer, "%d %d %d", &r1, &r2, &r3) == 3) {
                                set_ring_settings(r1, r2, r3);
                            } else {
                                printf("Invalid input for ring settings.\n");
                            }
                            break;
                        }

                        case '4':
                            break;

                        default:
                            printf("Invalid option. Please choose 1-4.\n");
                    }
                } while (config_choice != '4');
                break;
            }

            case 'L':
                load_config();
                printf("Configuration loaded successfully.\n");
                break;

            case 'S':
                save_config();
                printf("Configuration saved successfully.\n");
                break;

            case 'R': {
                printf("Reset all Enigma settings to defaults? (y/n): ");
                char confirmation = get_menu_choice();
                printf("%c\n", confirmation);
                if (confirm(confirmation)) {
                    reset_rotors();
                    reset_plugboard();
                    printf("All settings reset to defaults.\n");
                }
                break;
            }

            case 'Q':
                printf("Exiting Enigma Simulator. Goodbye!\n");
                return 0;

            default:
                printf("Invalid selection. Please choose E, D, C, L, S, R, or Q.\n");
        }
    }

    return 0;
}
