#include<lpc21xx.h>
#include"header.h"
float temp_convert(unsigned int adc_val)
{
    float voltage_mv = (adc_val * 3300.0) / 1023.0;
    float temp_c = voltage_mv / 10.0;
    return temp_c;
}



