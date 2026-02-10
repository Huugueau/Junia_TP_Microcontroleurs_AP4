/* 
 * File:   main.c
 * Author: Huugueau
 *
 * Created on January 27, 2026, 1:46 PM
 */

#include <xc.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <../Ressources/configbits.h>
#include <../Ressources/spi.h>
#include <../Ressources/lcd.h>

#define _XTAL_FREQ 8000000

/*
 * 
 */

void initInterupt() {
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    RCIE = 1;
}

void initPot() {
    TRISAbits.TRISA0 = 1;
    ANSELAbits.ANSA0 = 1;
    
    ADCON0bits.CHS = 0b00000;
    ADCON1bits.ADFM = 0;
    ADCON0bits.ADON = 1;
}

void initButton() {
    TRISAbits.TRISA5 = 1;
    ANSELAbits.ANSA5 = 0;
}

unsigned char readPot() {
    ADCON0bits.GO = 1;
    while(ADCON0bits.GO);
    return ADRESH;
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

void transmitc(char c) {
    while(!TXIF);
    TX1REG = c;
}

void transmit(char* c) {
    int i = 0;
    while(c[i] != '\0') {
        while(!TXIF);
        TX1REG = c[i];
        i++;
        __delay_ms(1);
    }
    /*while(*c) {
        transmitc(*c++);
    }*/
}



void initAll() {
    initInterupt();
    initEUSART();
    initIO();
    initBaudrate();
    initPot();
    initButton();
    activateUART();
    SPI_InitializePins();
    SPI_Initialize();
    LCD_InitializePins();
    LCD_Initialize();
    LCD_Clear();
    LCD_GoTo(0,0);
}

const char* alphabet = "0123456789abcdefghijklmnopqrstuvwxyz";
int offset;
int transformType = 1;

void transform(char* str) {
    int alphabetLen = strlen(alphabet);
    for(int i = 0; str[i] != '\0'; i++) {
        str[i] = tolower(str[i]);
        char* pos = strchr(alphabet, str[i]);
        if(pos != NULL) {
            int indexOf = pos - alphabet;
            // Use modulo to wrap around
            str[i] = alphabet[(indexOf + offset) % alphabetLen];
        }
    }
    // Don't transmit here - do it in ISR after this function returns
}

void detransform(char* str) {
    int alphabetLen = strlen(alphabet);
    for(int i = 0; str[i] != '\0'; i++) {
        str[i] = tolower(str[i]);
        char* pos = strchr(alphabet, str[i]);
        if(pos != NULL) {
            int indexOf = pos - alphabet;
            // Add alphabetLen before modulo to handle negative results
            str[i] = alphabet[(indexOf - offset + alphabetLen) % alphabetLen];
        }
    }
}

char* str;
int str_size = 128;
int index = 0;

void __interrupt() isr(void) {
    if(RCIF) {
        char received = RC1REG;
        
        if(received == '\r' || received == '\n') {
            str[index] = '\0';
            
            // Echo original
            transmit(str);
            transmit(" -> ");
            
            // Transform and send
            if(transformType == 1) {
                transform(str);
            } else {
                detransform(str);
            }
            transmit(str);
            transmit("\r\n");
            
            index = 0;
        } else if(index < str_size - 1) {
            str[index] = received;
            index++;
        }
    }
}



void main(void) {
    
    initAll();
    str = malloc(str_size * sizeof(char));
    transmit("Hello World!\n\r");
    char lcdBuffer[20];
    int lastOffset;
    int lastTransformType;
    while(1) {
        offset = (readPot() * 35 /255);
        
        if(PORTAbits.RA5 == 0) {
            while(PORTAbits.RA5 == 0);
            transformType = transformType == 1 ? 0 : 1;
        }
        
        if(offset != lastOffset || transformType != lastTransformType)  {
            lastTransformType = transformType;
            lastOffset = offset;
            LCD_Clear();
            sprintf(lcdBuffer, "Offset: %d", (readPot() * 35 / 255));
            LCD_WriteString(lcdBuffer);
            LCD_GoTo(1, 0);
            sprintf(lcdBuffer, "Type (%d): %s", transformType, (transformType == 1 ? "Codage" : "Decodage"));
            LCD_WriteString(lcdBuffer);
        }
        
        
    }
    return;
}

