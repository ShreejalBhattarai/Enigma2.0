#include "rotors.h"
#include <stdio.h>

static int rotor_positions[3];
static int ring_settings[3];
static int rotor_order[3];

static const int ROTORS[5][ALPHABET_SIZE] = {
    {4,10,12,5,11,6,3,16,21,25,13,19,14,22,24,7,23,20,18,15,0,8,1,17,2,9},
    {0,9,3,10,18,8,17,20,23,1,11,7,22,19,12,2,16,6,25,13,15,24,5,21,14,4},
    {1,3,5,7,9,11,2,15,17,19,23,21,25,13,24,4,8,22,6,0,10,12,20,18,16,14},
    {4,18,14,21,15,25,9,0,24,16,20,8,17,7,23,11,13,5,19,6,10,3,2,12,22,1},
    {21,25,1,17,6,8,19,24,20,15,18,3,13,7,11,23,0,22,12,9,16,14,5,4,2,10}
};

static const int ROTOR_NOTCHES[5] = {16, 4, 21, 9, 25};

static const int REFLECTOR_B[ALPHABET_SIZE] = {
    24,17,20,7,16,18,11,3,15,23,
    13,6,14,10,12,8,4,1,5,25,
    2,22,21,9,0,19
};

static int mod26(int x) {
    return (x % 26 + 26) % 26;
}

void rotors_init() {
    for (int i = 0; i < 3; i++) {
        rotor_positions[i] = 0;
        ring_settings[i] = 0;
        rotor_order[i] = i;
    }
}

void rotors_set_order(int r1, int r2, int r3) {
    rotor_order[0] = r1 - 1;
    rotor_order[1] = r2 - 1;
    rotor_order[2] = r3 - 1;
}

void rotors_set_ring_settings(int r1, int r2, int r3) {
    ring_settings[0] = r1 - 1;
    ring_settings[1] = r2 - 1;
    ring_settings[2] = r3 - 1;
}

static int rotor_forward_transform(int c, int rotor_num) {
    int pos = rotor_positions[rotor_num];
    int ring = ring_settings[rotor_num];
    int offset = mod26(c + pos - ring);
    int wired = ROTORS[rotor_order[rotor_num]][offset];
    return mod26(wired - pos + ring);
}

static int rotor_backward_transform(int c, int rotor_num) {
    int pos = rotor_positions[rotor_num];
    int ring = ring_settings[rotor_num];
    int offset = mod26(c + pos - ring);
    int wired = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (ROTORS[rotor_order[rotor_num]][i] == offset) {
            wired = i;
            break;
        }
    }
    return mod26(wired - pos + ring);
}

void rotors_step() {
    int r0 = rotor_positions[0];
    int r1 = rotor_positions[1];

    int notch0 = ROTOR_NOTCHES[rotor_order[0]];
    int notch1 = ROTOR_NOTCHES[rotor_order[1]];

    // Double stepping logic
    if (r0 == notch0) {
        rotor_positions[1] = mod26(r1 + 1);
        rotor_positions[0] = mod26(r0 + 1);
    }
    else if (r1 == notch1) {
        rotor_positions[1] = mod26(r1 + 1);
        rotor_positions[0] = mod26(r0 + 1);
    }
    else {
        rotor_positions[0] = mod26(r0 + 1);
    }
}

int rotor_forward(int c, int rotor_num) {
    return rotor_forward_transform(c, rotor_num);
}

int rotor_backward(int c, int rotor_num) {
    return rotor_backward_transform(c, rotor_num);
}

int reflector_reflect(int c) {
    return REFLECTOR_B[c];
}
