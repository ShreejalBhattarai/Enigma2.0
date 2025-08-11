#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define ALPHABET_SIZE 26

// Input processing
void clean_input(const char *input_raw, char *input_clean);
void process_message(char *message);

// Menu and user interaction
char get_menu_choice();
int confirm(char c);

// Enigma machine controls
void reset_rotors();
void setup_leds();
void set_rotor_order(int a, int b, int c);
void set_ring_settings();
void load_config();
void save_config();
void clear_stdin();

// Encode single character with full machine process
char encode_char(char c);

// Helper for letter index wrap-around
int mod26(int x);

#endif
