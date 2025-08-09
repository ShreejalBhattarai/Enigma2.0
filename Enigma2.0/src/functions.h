#ifndef FUNCTIONS_H
#define FUNCTIONS_H

char get_menu_choice();
void reset_rotors();
void setup_leds();
void clean_input(const char *input_raw, char *input_clean);
void set_rotor_order (int a, int b, int c);
void set_ring_settings ();
int confirm(char inputgiven);
char enigma_encrypt(const char ch); 
void load_config();
void save_config();
void process_message(const char *message);
void step_rotors();
#endif
