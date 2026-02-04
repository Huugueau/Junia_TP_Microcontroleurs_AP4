/* 
 * File:   main.c
 * Author: Huugueau
 *
 * Created on January 27, 2026, 1:46 PM
 */

#include <xc.h>
#include "../Ressources/configbits.h"
#include "../Ressources/spi.h"
#include "../Ressources/lcd.h"

#define _XTAL_FREQ 8000000

/*
 * 
 */

void initInterupt() {
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    RCIE = 1;
}

void initEUSART() {
    
    RC6PPS = 0b00010100;
    RXPPS = 0b00010111;
}

void activateUART() {
    SPEN = 1;
    TXEN = 1;
    CREN = 1;
}

void initIO() {
    TRISC6 = 0;
    TRISC7 = 1;
    
    ANSELC = 0;
    LATC = 0;
}

void initBaudrate() {
    SYNC = 0;
    BRGH = 0;
    BRG16 = 0;
    SP1BRGH = 0;
    SP1BRGL = 12;
}

void transmit(const char* c) {
    int i = 0;
    while(c[i] != '\0') {
        while(!TXIF);
        TX1REG = c[i];
        i++;
    }
}

void initAll() {
    initInterupt();
    initEUSART();
    initIO();
    initBaudrate();
    activateUART();
    SPI_InitializePins();
    SPI_Initialize();
    LCD_InitializePins();
    LCD_Initialize();
    LCD_Clear();
    LCD_GoTo(0,0);
}

void __interrupt() isr(void) {
    if(RCIF) {
        char c = RC1REG;
        char str[4] = {c, '\n', '\r', '\0'};
        transmit("Echo: ");
        transmit(str);
    }
} 


void main(void) {
    
    
    initAll();
    LCD_WriteString("Hello World!");
    //transmit("Hello World!\n\r");
    while(1) {}
    return;
}

