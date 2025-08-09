#include <stdio.h>
#include "functions.h"
#include <ctype.h>
#include "plugboard.h"


const char ROTOR_I_WIRING[] =   "EKMFLGDQVZNTOWYHXUSPAIBRCJ";
const char ROTOR_II_WIRING[] =  "AJDKSIRUXBLHWTMCQGZNPYFVOE";
const char ROTOR_III_WIRING[] = "BDFHJLCPRTXVZNYEIWGAKMUSQO";

// Rotor positions: 0 = 'A', 1 = 'B', ..., 25 = 'Z'
int rotor_positions[3] = {0, 0, 0}; // Left, Middle, Right

// Notch positions for rotors I, II, III
int notch_positions[3] = {
    'Y' - 'A', // Rotor I notch
    'M' - 'A', // Rotor II notch
    'D' - 'A'  // Rotor III notch
};


#define ALPHABET_SIZE 26 


const char REFLECTOR_B_WIRING[] = "YRUHQSLDPXNGOKMIEBFZCWVJAT";
const char ROTOR_NOTCHES[] = {'Y', 'M', 'D', ' ', ' '};

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

void process_message(const char *message) {
    for (int i = 0; message[i] != '\0'; i++) {
        char ch = message[i]; 

        step_rotors();                          // Step before encryption
        apply_plugboard_mapping(&ch);           // Plugboard input
        char enc = enigma_encrypt(ch);          // Through rotors + reflector
        apply_plugboard_mapping(&enc);          // Plugboard output

        printf("%c", enc);
    }
    printf("\n"); 
}


//Dummy-----> Not currently implemented
char enigma_encrypt(const char ch) {
    return ch;
}

void set_rotor_order(int a, int b, int c) {
    printf("Rotor order set to: %d %d %d\n", a, b, c);
}

void step_rotors() {
    // Double-stepping logic:
    // If middle rotor is at its notch, step middle AND left
    if (rotor_positions[1] == notch_positions[1]) {
        rotor_positions[0] = (rotor_positions[0] + 1) % ALPHABET_SIZE; // Step left
        rotor_positions[1] = (rotor_positions[1] + 1) % ALPHABET_SIZE; // Step middle
    }

    // If right rotor is at its notch, step middle
    if (rotor_positions[2] == notch_positions[2]) {
        rotor_positions[1] = (rotor_positions[1] + 1) % ALPHABET_SIZE;
    }

    // Always step right rotor
    rotor_positions[2] = (rotor_positions[2] + 1) % ALPHABET_SIZE;
}

void clean_input(const char *input_raw, char *input_clean) {
    int j = 0;
    for (int i = 0; input_raw[i] != '\0'; i++) {
        if (isalpha((unsigned char)input_raw[i])) {  
            input_clean[j++] = toupper((unsigned char)input_raw[i]);
        }
    }
    input_clean[j] = '\0'; // Null-terminate
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
