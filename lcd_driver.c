#include<lpc21xx.h>
#include"header.h"
void lcd_cmd(unsigned char cmd)
{
    IOCLR1 = LCD_RS;                 
    lcd_write_nibble(cmd >> 4);      
  	lcd_write_nibble(cmd & 0x0F);    
    delay_ms(2);
}

void lcd_data(unsigned char data)
{
    IOSET1 = LCD_RS;                 
    lcd_write_nibble(data >> 4);
    lcd_write_nibble(data & 0x0F);
    delay_ms(2);
}

void lcd_string(char *str)
{
    while (*str)
        lcd_data(*str++);
}

void lcd_init(void)
{
    delay_ms(20);            
  	lcd_cmd(0x02);            
    lcd_cmd(0x28);            
    lcd_cmd(0x0C);          
    lcd_cmd(0x06);          
    lcd_cmd(0x01);            
    delay_ms(2);
}


void lcd_set_cursor(unsigned char row, unsigned char col)
{
    unsigned char addr = (row == 0) ? (0x80 + col) : (0xC0 + col);
    lcd_cmd(addr);
}


void lcd_pulse_enable(void)
{
    IOSET1 = LCD_EN;
    delay_ms(1);
    IOCLR1 = LCD_EN;
    delay_ms(1);
}

void lcd_write_nibble(unsigned char nibble)
{
    IOCLR1 = LCD_DATA_MASK;
    if (nibble & 0x1) IOSET1 = LCD_D4;
    if (nibble & 0x2) IOSET1 = LCD_D5;
    if (nibble & 0x4) IOSET1 = LCD_D6;
    if (nibble & 0x8) IOSET1 = LCD_D7;
    lcd_pulse_enable();
}




void print_uint(void (*out)(char), unsigned int n)
{
    char rev[6];
    int r_idx = 0, i;
    if (n == 0) rev[r_idx++] = '0';
    while (n > 0) { rev[r_idx++] = (n % 10) + '0'; n /= 10; }
    for (i = r_idx - 1; i >= 0; i--) out(rev[i]);
}
void lcd_out_char(char c) { lcd_data(c); }
void uart_out_char(char c) { uart0_send_char(c); }





