#include "pico/stdlib.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "functions.h"

void print_banner() {
    printf("\n");
    printf("╔═════════════════════════════════════════════════════════╗\n");
    printf("║                   ENIGMA 2.0                            ║\n");
    printf("║   Electronic Replica of the original cipher machine.    ║\n");
    printf("╚═════════════════════════════════════════════════════════╝\n");
}

void print_menu() {
    printf("\nMain Menu:\n");
    printf("  [E] Encrypt Message\n");
    printf("  [D] Decrypt Message\n");
    printf("  [C] Configure Machine\n");
    printf("  [L] Load Config\n");
    printf("  [S] Save Config\n");
    printf("  [R] Reset All Settings\n");
    printf("  [Q] Quit\n");
}

char get_menu_choice() {
    char choice;
    printf("Select option: ");
    scanf(" %c", &choice);
    return toupper(choice);
}
