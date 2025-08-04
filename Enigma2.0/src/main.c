#include <stdio.h>
#include <string.h>  
#include <ctype.h>
#include "functions.h"
#include "plugboard.h"
#include "ui_functions.h"
#include "pico/stdlib.h"

#define MAX_MESSAGE_LENGTH 512 
#define SLEEP_TIME_MS 2000   


int main() {
     char input_raw[MAX_MESSAGE_LENGTH];   // Buffer for raw user input
    char input_clean[MAX_MESSAGE_LENGTH]; // Buffer for cleaned (uppercase, alpha-only) input

    stdio_init_all();
    sleep_ms(SLEEP_TIME_MS);

    reset_rotors();
    printf("Resetting Rotors.\n");
    setup_leds();
    printf("Resetting LED's.\n");
    reset_plugboard();
    printf("Resetting Plugboard.\n");

    //green flag
    greet_user();

    sleep_ms(SLEEP_TIME_MS);

    print_banners();

    sleep_ms(SLEEP_TIME_MS);

    while (true) {
        print_menu();
        char choice = get_menu_choice();

        switch (choice){
            case 'E':
            case 'D':
                reset_rotors();
                printf("Enter your message: ");
                
                int c;
                while ((c = getchar()) != '\n' && c!= EOF);
                if (fgets(input_raw, MAX_MESSAGE_LENGTH, stdin) != NULL) {
                    input_raw[strcspn(input_raw, "\n")] = 0;
                } else {
                    printf("Error reading input. Please try again.\n");
                    break;
                }

                if (strlen(input_clean) == 0) {
                    printf("No valid letters to process. Please try again with letters.\n");
                    break;
                }


                printf("Output: ");
                process_message(input_clean); 
                break;

            case 'C':
            {
                char config_choice;
                    do {
                        printf("\n--- Configuration Menu ---\n");
                        printf("[1] Set Plugboard\n");
                        printf("[2] Set Rotor Order\n");
                        printf("[3] Set Ring Settings\n");
                        printf("[4] Back to Main Menu\n");
                        printf("Choose: ");
                        scanf(" %c", &config_choice); 
                        int a,b,c;
                        switch (config_choice) {
                            case '1': set_plugboard(); break;     
                            case '2': printf("Please Enter the Rotor Order. \n"); scanf("%d, %d, %d", 'a', 'b', 'c'); set_rotor_order(a, b, c); break;   
                            case '3': set_ring_settings(); break; 
                            case '4': break;                      
                            default: printf("Invalid option. Please choose 1-4.\n");
                        }
                    } while (config_choice != '4');
                    break;
                }

            case 'L':
                    {
                    load_config(); 
                    printf("Configuration loaded successfully.\n");
                    }
                break;


            case 'S':
            {
                    save_config(); 
                    printf("Configuration saved successfully.\n");
                }
                break;


            case 'R':
            char confirmation;
            printf("Reset all Enigma settings to defaults? (y/n): ");
            scanf("%c", &confirmation);
                if (confirm(confirmation)) {
                    reset_rotors();   
                    reset_plugboard(); 
                printf("All settings reset to defaults.\n");
                }
                break;
            case 'Q':
                printf("Exiting Enigma Simulator. Goodbye!\n");
                return 0;
            default:
                printf("Invalid Selection. Please choose E, D, C, L, S, R, or Q.\n");
        } 
    }
    return 0;
}

