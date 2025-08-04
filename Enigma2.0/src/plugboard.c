#include <stdio.h>
#include "plugboard.h"

#define ALPHABET_SIZE 26

void set_plugboard() {

}

void reset_plugboard() {
    int plugboard_mapping[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        plugboard_mapping[i] = i; // A maps to A, B to B, etc.
    }
}

void apply_plugboard_mapping(char* message) {

}
