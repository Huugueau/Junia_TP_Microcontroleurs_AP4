
#include <xc.h>


void nextLight2(int light){
    LATB &= 0x00;
    LATBbits.LATB3 = light == 0 ? 1 : 0;
    LATBbits.LATB2 = light == 1 ? 1 : 0;
    LATBbits.LATB1 = light == 2 ? 1 : 0;
    LATBbits.LATB0 = light == 3 ? 1 : 0;
}

void nextLight(int light) {
    LATD &= 0x00;
    LATDbits.LATD0 = light == 0 ? 1 : 0;
    LATDbits.LATD1 = light == 1 ? 1 : 0;
    LATDbits.LATD2 = light == 2 ? 1 : 0;
    LATDbits.LATD3 = light == 3 ? 1 : 0;
  
}

void initLeds(void) {
    TRISD &= 0xF0;
    TRISB &= 0xF0;
}
