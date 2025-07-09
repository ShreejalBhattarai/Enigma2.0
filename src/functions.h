#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdbool.h>

// ───── ROTOR MODULE ─────

// Resets rotors to default position
void reset_rotors(void);

// Steps the rotors after each character
void step_rotors(void);

// Encrypts a character through the Enigma rotors
char enigma_encrypt(char ch);

// ───── PLUGBOARD MODULE ─────

// Sets plugboard mappings from user input
void set_plugboard(void);

// Applies plugboard mapping before rotor pass
void apply_plugboard_mapping(char *ch);

// Reverses plugboard mapping after rotor pass
void reverse_plugboard_mapping(char *ch);

// Clears all plugboard connections
void reset_plugboard(void);

// ───── LED MODULE ─────

// Initializes all LEDs (GPIO setup)
void setup_leds(void);

// Blinks the LED corresponding to a given letter
void blink_led_for_letter(char ch);

// ───── CONFIG MODULE (FLASH / EEPROM) ─────

// Loads config from persistent storage
void load_config(void);

// Saves current config to persistent storage
void save_config(void);

// ───── UI UTILITIES ─────

// Confirms an action with user (yes/no)
bool confirm(const char *prompt);

#endif // FUNCTIONS_H
