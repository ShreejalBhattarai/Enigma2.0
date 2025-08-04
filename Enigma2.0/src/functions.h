#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// void set_rotor_order(int a, int b, int c);
char get_menu_choice();
void reset_rotors();
void setup_leds();
void set_rotor_order (int a, int b, int c);
void set_ring_settings ();
int confirm(char inputgiven);
void load_config();
void save_config();
void process_message(const char *message);
char enigma_encrypt(char ch);
void step_rotors();
#endif
