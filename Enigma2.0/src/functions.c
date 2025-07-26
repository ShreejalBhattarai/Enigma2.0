#include <stdio.h>
#include "functions.h"

void set_rotor_order(int a, int b, int c) {
    printf("Rotor order set to: %d %d %d\n", a, b, c);
}

char get_menu_choice() {
    char choice;
    scanf("%c", &choice);
    return toupper(choice);
}
