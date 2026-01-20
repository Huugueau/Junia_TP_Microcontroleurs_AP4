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

void initTimerAndInterupts() {
    PR2 = 255;
    T2CON = 0b00000111;
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    PIE1bits.TMR2IE = 1;
    
}

void initLED(){           
    TRISDbits.TRISD0 = 0;
}

int count;
int direction;

void __interrupt() isr(void) {
    if(TMR2IE && TMR2IF) {
            TMR2IF = 0;
            if(direction == 1) count--;
            else count++;
            if(count == 126 || count == 0) {
                direction = direction == 1 ? 0 : 1;
            }
            initPWM(count);
        }
}

void main(void) {

    
    initLED();
    initTimerAndInterupts();
    initPPS();
    
    while(1) {
    }
    
    
}
