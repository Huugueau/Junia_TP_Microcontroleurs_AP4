/*
 * File:   main.c
 * Author: root
 *
 * Created on January 20, 2026, 3:25 PM
 */

#include "../Ressources/configbits.h"
#include <xc.h>

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

void initPot(){
    TRISAbits.TRISA0 = 1;
    ANSELAbits.ANSA0 = 1;
    
    ADCON0bits.CHS = 0b00000; 
    ADCON1bits.ADFM = 0; 
    ADCON0bits.ADON = 1; 
}
unsigned char readPot(){
    ADCON0bits.GO =1;
    while(ADCON0bits.GO){}
    return ADRESH;
}

void initLeds(void) {
    TRISD &= 0xF0;
    TRISB &= 0xF0;
}

void main(void) {
    int light;
    initLeds();
    initPot();
    while(1){
        light = readPot() / 32;
        nextLight(light);
    }
}
