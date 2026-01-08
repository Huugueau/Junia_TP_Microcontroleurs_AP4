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


void initTimer() {
    PR2 = 0b01111101;
    T2CON = 0b00000110;
}

void nextLight(int light) {
    LATD &= 0x00;
    LATB &= 0x00;
    LATDbits.LATD0 = light == 0 ? 1 : 0;
    LATDbits.LATD1 = light == 1 ? 1 : 0;
    LATDbits.LATD2 = light == 2 ? 1 : 0;
    LATDbits.LATD3 = light == 3 ? 1 : 0;
    LATBbits.LATB0 = light == 4 ? 1 : 0;
    LATBbits.LATB1 = light == 5 ? 1 : 0;
    LATBbits.LATB2 = light == 6 ? 1 : 0;
    LATBbits.LATB3 = light == 7 ? 1 : 0;

}

void main(void) {

    initTimer();
    TRISD &= 0xF0;
    TRISB &= 0xF0;
    int count = 0;
    int light = 0;
    while(1) {
        
        if(TMR2IF) {
            TMR2IF = 0;
            count++;
            if(count == 125) {
                if(light == 8) light = 0;
                nextLight(light);
                light++;
                count = 0;
            }
        }
    
    }
}

