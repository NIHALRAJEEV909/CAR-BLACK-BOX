#include <xc.h>
#include "CBB_main.h"

unsigned int sec = 60;
unsigned int count0 = 0;

void __interrupt() isr(void) {
    
    if (TMR0IF) {
        TMR0 = TMR0 + 8;

        if (count0++ == 20000) {
            sec--;
            count0 = 0;

        }
        TMR0IF = 0;
    }
}