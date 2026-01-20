/*
 * File:   main.c
 * Author: root
 *
 * Created on January 20, 2026, 3:25 PM
 */

#include "../Ressources/configbits.h"
#include <xc.h>

void initLeds(void) {
    TRISD &= 0xF0;
    TRISB &= 0xF0;
}

void main(void) {
    initLeds();
    while(1){
    }
}
