#include<lpc21xx.h>
#include"header.h"
void uart0_init(void)
{
    PINSEL0 |= 0x00000005;   // P0.0 = TXD0, P0.1 = RXD0
    U0LCR = 0x83;             // 8 bits, 1 stop, no parity, enable DLAB
    U0DLL = 97;                // Baud rate divisor for 9600 @ 15MHz PCLK
    U0DLM = 0;
    U0LCR = 0x03;             // disable DLAB, 8N1 mode locked in
}

void uart0_send_char(char c)
{
    U0THR = c;
    while (!(U0LSR & 0x20));  // wait until THR is empty (ready for next byte)
}

void uart0_send_string(char *str)
{
    while (*str)
        uart0_send_char(*str++);
}
