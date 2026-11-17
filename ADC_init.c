#include<lpc21xx.h>
#include"header.h"
void adc_init(void)
{ 
	  PINSEL1 |= (1 << 22);   // P0.28 -> AD0.1 (LM35)
    PINSEL1 |= (1 << 24);   // P0.29 -> AD0.2 (LDR)
    PINSEL1 |= (1 << 26);   // P0.30 -> AD0.3 (Soil Moisture)

    ADCR = (4 << 8)        // CLKDIV
           | (1 << 21);     // PDN = power up ADC block (SEL set per-read)
	
}


unsigned int adc_read(unsigned char channel)
{
    unsigned int val;
  	ADCR &= ~0xFF;                  
    ADCR |= (1 << channel);          
    ADCR |= (1 << 24);              
    while (!(ADDR & 0x80000000));  
    val = (ADDR >> 6) & 0x3FF;     
    ADCR &= ~(1 << 24);            
  	return val;
}











