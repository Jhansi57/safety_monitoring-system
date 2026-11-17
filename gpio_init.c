#include<lpc21xx.h>
#include"header.h"


void gpio_init(void)
{
    IODIR0 |= (LED_GREEN | LED_YELLOW | LED_RED);   
   	IODIR0 &= ~(WATER_PIN);                          

    IODIR1 |= (LCD_RS | LCD_EN | LCD_DATA_MASK);     
	  IOCLR0 = (LED_GREEN | LED_YELLOW | LED_RED);
}

