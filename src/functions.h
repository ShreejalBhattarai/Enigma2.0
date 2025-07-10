#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdbool.h>

// ----- UI MODULE -----
void print_menu();

void print_banner();

void get_menu_choice();

// ───── ROTOR MODULE ─────

void reset_rotors(void);

void step_rotors(void);

char enigma_encrypt(char ch);

// ───── PLUGBOARD MODULE ─────

void set_plugboard(void);

void apply_plugboard_mapping(char *ch);

void reverse_plugboard_mapping(char *ch);

void reset_plugboard(void);

// ───── LED MODULE ─────

void setup_leds(void);

void blink_led_for_letter(char ch);

// ───── CONFIG MODULE (FLASH / EEPROM) ─────

void load_config(void);

void save_config(void);

// ───── UI UTILITIES ─────

// Confirms an action with user (yes/no)
bool confirm(const char *prompt);

#endif // FUNCTIONS_H
