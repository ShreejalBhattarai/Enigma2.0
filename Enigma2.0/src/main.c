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
                printf("Enter your message: \n");
                fflush(stdout);

                char input_buffer[INPUT_BUFFER_SIZE];
                char input_clean[INPUT_BUFFER_SIZE];

                // Read a full line safely
                if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
                    printf("Error reading input. Please try again.\n");
                    break; // Exit the switch case on error
                }

                // Check if a newline was found and strip it.
                // If not found, the buffer was filled, and we need to clear stdin.
                char *newline_pos = strchr(input_buffer, '\n');
                if (newline_pos != NULL) {
                    *newline_pos = '\0'; // Newline found, strip it
                } else {
                    // Newline NOT found: input line was longer than buffer.
                    // Clear the rest of the overly long line from stdin.
                    printf("Warning: Input truncated due to length limit. Clearing buffer.\n");
                    clear_stdin(); // Call helper to clear remaining chars
                }
                printf("before clean input");

                // Clean input (only letters, uppercase)
                clean_input(input_buffer, input_clean);

                if (strlen(input_clean) == 0) {
                    printf("No valid letters to process. Please try again with letters.\n");
                    break; // Exit the switch case if no valid letters
                }

                printf("Output: ");
                process_message(input_clean);
                printf("\n\n"); // Added for better output formatting
                // No break here, as it's already handled by the switch case
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
                                set_ring_settings();  // You might want to pass these or handle here instead
                                set_ring_settings(r1, r2, r3);
                                printf("Ring settings set to: %d %d %d\n", r1, r2, r3);
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
