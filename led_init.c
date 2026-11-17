#include<lpc21xx.h>
#include"header.h"

void led_update(unsigned char alert, unsigned char warning)
{
    IOCLR0 = (LED_GREEN | LED_YELLOW | LED_RED);
    if (alert)
        IOSET0 = LED_RED;
    else if (warning)
        IOSET0 = LED_YELLOW;
    else
        IOSET0 = LED_GREEN;
}
