#include <xc.h>
#include "../Ressources/configbits.h"
#include "../Ressources/leds.h"
#include "../Ressources/timer.h"

int count;
int light;
int on = 1;

void initIOC() {
    INTCONbits.IOCIE = 1;
    IOCANbits.IOCAN5 = 1;
}

void initButton() {
    TRISAbits.TRISA5 = 1;
    ANSELAbits.ANSA5 = 0;
}

void __interrupt() isr(void) {
    if (on == 1 && TMR2IE && TMR2IF) {
        TMR2IF = 0;
        count++;
        if (count == 125) {
            if (light == 4) light = 0;
            nextLight(light);
            light++;
            count = 0;
        }
    }
    if (IOCAF5) {
        IOCAF5 = 0;
        if (on == 1) on = 0;
        else on = 1;
    }
}

void main(void) {


    initTimerAndInterupts();
    initLeds();
    initButton();
    initIOC();
    LATD &= 0x00;
    LATB &= 0x00;
    int count;
    int light;
    
    while(1) {
        if (TMR2IF) {
            TMR2IF = 0;
            count++;
            if(count == 125) {
                if(light == 4) light = 0;
                nextLight2(light);
                light++;
                count = 0;
            }
        }
    }
        

}


