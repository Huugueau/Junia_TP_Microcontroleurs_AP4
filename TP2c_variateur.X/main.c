/*
 * File:   main.c
 * Author: Huugueau
 *
 * Created on January 20, 2026, 3:30 PM
 */

#include <xc.h>
#include "../Ressources/configbits.h"

void initPPS(){
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0; 
    
    RD0PPS = 15;
    PPSLOCKbits.PPSLOCKED = 1;
}

void initPWM(unsigned char value){
    PWM4DCH = value;
    PWM4DCL = 0;
    
    PWM4CONbits.PWM4EN = 1;
}

void initTimer(){
    PR2 = 255;
    T2CON = 0b00000110;
}

void initLED(){           
    TRISDbits.TRISD0 = 0;
}

void initADC(){
    TRISAbits.TRISA0 = 1;
    ANSELAbits.ANSA0 = 1;
    
    ADCON0bits.CHS = 0b00000; 
    ADCON1bits.ADFM = 0; 
    ADCON0bits.ADON = 1; 
}

unsigned char readADCValue() {
    ADCON0bits.GO = 1;
    while(ADCON0bits.GO);
    return ADRESH;  
}

void main(void) {

    
    initLED();
    initPWM(200);
    initTimer();
    initPPS();
    initADC();
    
    while(1) {
        unsigned char value = readADCValue();
        initPWM(value);
    }
    
    
}
