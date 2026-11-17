
#include<lpc21xx.h>
#include"header.h"
unsigned int ldr_read(void)
{
    return adc_read(CH_LDR);
}

