
#include<lpc21xx.h>

#include"header.h"


unsigned char water_read(void)
{
    return (IOPIN0 & WATER_PIN) ? 0 : 1;   // 1 = water detected
	//return 1;
}

