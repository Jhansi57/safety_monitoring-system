
#include<lpc21xx.h>
#include"header.h"
unsigned int soil_read_percent(void)
{
    unsigned int raw = adc_read(CH_SOIL);
    return (raw * 100) / 1023;
}
