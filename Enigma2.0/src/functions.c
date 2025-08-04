#include <stdio.h>
#include "functions.h"
#include <ctype.h>


// Rotor wirings (historical Enigma I rotors)
// These strings represent the fixed internal wiring of each physical rotor.
// E.g., for ROTOR_I_WIRING, 'A' (index 0) maps to 'E' (index 4), 'B' (index 1) maps to 'K' (index 10), etc.
const char ROTOR_I_WIRING[] =   "EKMFLGDQVZNTOWYHXUSPAIBRCJ";
const char ROTOR_II_WIRING[] =  "AJDKSIRUXBLHWTMCQGZNPYFVOE";
const char ROTOR_III_WIRING[] = "BDFHJLCPRTXVZNYEIWGAKMUSQO";



#define ALPHABET_SIZE 26 // The size of the English alphabet (A-Z)


const char REFLECTOR_B_WIRING[] = "YRUHQSLDPXNGOKMIEBFZCWVJAT";


// Notches (points where the rotor causes the next rotor to its left to step)
// These correspond to the letter on the rotor's ring where the notch is located.
// For Enigma I: Rotor I (Y), Rotor II (M), Rotor III (D).
// The array index corresponds to the physical rotor ID (0 for I, 1 for II, 2 for III).
// We pad it with spaces for potential future rotors (IV, V) if they were added.
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
        char ch = message[i]; // Get the current character

        // 1. Apply plugboard mapping for the input character (from functions.c)
        apply_plugboard_mapping(&ch);

        // 2. Encrypt/Decrypt the character through the rotors and reflector (from functions.c)
        char enc = enigma_encrypt(ch);

        // 3. Apply plugboard mapping again for the output character (symmetric) (from functions.c)
        // apply_plugboard_mapping(&enc);

        // 4. Print the resulting character
        printf("%c", enc);

        // 5. Simulate the lampboard by blinking an LED (from functions.c)
        // blink_led_for_letter(enc); NOT GOING TO IMPLEMENT YET

        // 6. Step the rotors for the next character (from functions.c)
        step_rotors();
    }
    printf("\n"); // Print a newline after the message is fully processed
}


void set_rotor_order(int a, int b, int c) {
    printf("Rotor order set to: %d %d %d\n", a, b, c);
}

char enigma_encrypt(char ch) {

}

void step_rotors() {

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
