#include <stdio.h>
#include "functions.h"
#include <ctype.h>


char get_menu_choice() {
    char choice;
    scanf("%c", &choice);
    return toupper(choice);
}

int confirm(char inputgiven) {
    if (toupper(inputgiven) == 'Y') { 
        return 1; 
    } else {
        return 0; 
    }
}

void set_rotor_order(int a, int b, int c) {
    printf("Rotor order set to: %d %d %d\n", a, b, c);
}

void set_ring_settings() {

}

void reset_rotors() {
    
}


void setup_leds() {

}

void load_config() {

}

void save_config() {

}
