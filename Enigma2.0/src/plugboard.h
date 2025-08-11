#ifndef PLUGBOARD_H
#define PLUGBOARD_H

void reset_plugboard();
void set_plugboard();
char plugboard_get_mapping(int index);
void apply_plugboard_mapping(char *message);

#endif
