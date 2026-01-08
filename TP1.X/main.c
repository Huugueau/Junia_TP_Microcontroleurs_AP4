/*
 * File:   main.c
 * Author: apirog
 *
 * Created on January 5, 2026, 12:08 PM
 */

// Allume les LEDs D5-8 de la carte Microchip Explorer 8 
// MCU : PIC16F1719 
//
// | LED | Pin |
// |-----|-----|
// |  D5 | RB0 |
// |  D6 | RB1 |
// |  D7 | RB2 |
// |  D9 | RB3 |
//

#include <xc.h>
#include "../Ressources/configbits.h"

void delai_approx(void) {
    unsigned long i = 0;
    for(i = 0; i < 80000; i++) {}
}

void lights(int d) {
    if(d == 1) {
        LATDbits.LATD0 = 1;
        LATDbits.LATD1 = 1;
        LATDbits.LATD2 = 1;
        LATDbits.LATD3 = 1;
        LATBbits.LATB0 = 0;
        LATBbits.LATB1 = 0;
        LATBbits.LATB2 = 0;
        LATBbits.LATB3 = 0;
    } else {
        LATDbits.LATD0 = 0;
        LATDbits.LATD1 = 0;
        LATDbits.LATD2 = 0;
        LATDbits.LATD3 = 0;
        LATBbits.LATB0 = 1;
        LATBbits.LATB1 = 1;
        LATBbits.LATB2 = 1;
        LATBbits.LATB3 = 1;
    }
}

void main(void) {

    TRISD &= 0xF0;
    TRISB &= 0xF0;
    while(1) {
        lights(1);
        delai_approx();
        lights(0);
        delai_approx();
    }
}

