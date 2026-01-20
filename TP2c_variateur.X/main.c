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
    
    TRISDbits.TRISD1 = 0;
    RD0PPS = 15;
    PPSLOCKbits.PPSLOCKED = 1;
}

void initPWM(int value){
    PWM4DCH = value;
    PWM4DCL = 0;
    
    PWM4CONbits.PWM4EN = 1;
}

void initTimer(){
    PR2 = 0b11111111;
    T2CON = 0b00000110;
}

void initLED(){           
    TRISDbits.TRISD0 = 0;  
}

void initADC(void) {
    
    // 1
    TRISAbits.TRISA0 = 1;        // RA0 en entrée
    ANSELAbits.ANSA0 = 1;        // RA0 en mode analogique
    
    
    
    
    ADCON1bits.ADCS = 0b100;     // Fosc/4 (horloge de conversion)
    ADCON1bits.ADFM = 0;         // Justification à gauche 
    ADCON1bits.ADPREF = 0b00;    
    
    ADCON0bits.CHS = 0b00000;    // Sélection du canal AN0 (RA0)
    ADCON0bits.ADON = 1;         // Activer le module ADC
}

int readADCValue(void) {
    
    //__delay_us(5);               
    
    ADCON0bits.GO = 1;           // Démarrer la conversion
    
    while(ADCON0bits.GO);        // Attendre la fin de la conversion
    
    return ADRESH;  // Retourner la valeur 
}

void main(void) {

    
    initLED();
    initTimer();
    initPWM();
    initADC();
    
    while(1) {
        int value = readADCValue();
        initPWM(value);
    }
    
    
}
