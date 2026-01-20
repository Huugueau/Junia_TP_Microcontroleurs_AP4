#include <xc.h>
#include "../Ressources/configbits.h"

void initPPS(){
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0; 
    
    RD0PPS = 15;
    PPSLOCKbits.PPSLOCKED = 1;
}

void initPWML(){
    PWM4DCH = 12;
    PWM4DCL = 0;
    
    PWM4CONbits.PWM4EN = 1;
}

void initPWMH(){
    PWM4DCH = 120;
    PWM4DCL = 0;
    
    PWM4CONbits.PWM4EN = 1;
}

void initTimer(){
    PR2 = 0b01111000;
    T2CON = 0b00000110;
}

void initComponents(){        
    TRISAbits.TRISA5 = 1;  
    ANSELAbits.ANSA5 = 0;  
   
    TRISDbits.TRISD0 = 0;  
  
}

void main(void) {
    LATD &= 0x00;
    LATB &= 0x00;
    initComponents();
    initPWML();
    initTimer();
    initPPS();
    while(1) {
        if (PORTAbits.RA5 == 0) { 
            initPWMH();
        } else {
            initPWML();
        }
    }
}