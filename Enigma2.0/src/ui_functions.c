#include <stdio.h>
#include "ui_functions.h"

void greet_user() {
    printf("UI ready\n");
}

void print_banners() {
    printf("\n");
    printf("****************************************\n");
    printf("* *\n");
    printf("* Pico Enigma Simulator         *\n");
    printf("* *\n");
    printf("****************************************\n");
    printf("\n");
}

void print_menu() {
    printf("\n--- Main Menu ---\n");
    printf("[E] Encrypt Message\n");
    printf("[D] Decrypt Message\n");
    printf("[C] Configure Enigma (Rotors, Plugboard, Rings)\n");
    printf("[L] Load Configuration from Flash\n");
    printf("[S] Save Configuration to Flash\n");
    printf("[R] Reset All Settings to Defaults\n");
    printf("[Q] Quit\n");
    printf("Enter your choice: ");
}