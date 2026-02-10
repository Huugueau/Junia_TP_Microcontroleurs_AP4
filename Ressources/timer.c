
#include <xc.h>


void initTimerAndInterupts() {
    PR2 = 0b01111101;
    T2CON = 0b00000110;
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    PIE1bits.TMR2IE = 1;
}
