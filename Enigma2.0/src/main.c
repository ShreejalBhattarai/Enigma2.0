#include <stdio.h>
#include "functions.h"
#include "plugboard.h"
#include "ui_functions.h"
#include "pico/stdlib.h"


int main() {
    stdio_init_all();
    while (true) {
        printf("Hello from Pico!\n");
        sleep_ms(5000);
    }
    return 0;
}