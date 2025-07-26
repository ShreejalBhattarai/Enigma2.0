#include <stdio.h>
#include "functions.h"
#include "plugboard.h"
#include "ui_functions.h"
#include "pico/stdlib.h"

#define MAX_MESSAGE_LENGTH 512 
#define SLEEP_TIME_MS 2000   


int main() {
    stdio_init_all();
    sleep_ms(SLEEP_TIME_MS);

    //green flag
    greet_user();

    sleep_ms(SLEEP_TIME_MS);

    //setup_leds();
    print_banners();

    sleep_ms(SLEEP_TIME_MS);

    while (true) {
        print_menu();
        char choice = get_menu_choice();

        switch (choice){
            case 'E':
            case 'C':
            case 'D':
            case 'L':
            case 'S':
            case 'R':
            case 'Q':
            default:
                printf("Invalid Selection. Please choose E, D, C, L, S, R, or Q.\n");
        } 
    }
    return 0;
}