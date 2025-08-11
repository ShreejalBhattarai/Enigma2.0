#ifndef ROTORS_H
#define ROTORS_H

#define ALPHABET_SIZE 26

void rotors_init();
void rotors_set_order(int r1, int r2, int r3);
void rotors_set_ring_settings(int r1, int r2, int r3);
void rotors_step();
int rotor_forward(int c, int rotor_num);
int rotor_backward(int c, int rotor_num);
int reflector_reflect(int c);

#endif
