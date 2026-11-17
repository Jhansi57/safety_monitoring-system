

#include <lpc21xx.h>

/* LED Pin Definitions */
#define LED_GREEN       (1 << 17)
#define LED_YELLOW      (1 << 18)
#define LED_RED         (1 << 19)

/* Water Sensor */
#define WATER_PIN       (1 << 5)

/* LCD Pin Definitions - Port 1 */
#define LCD_RS          (1 << 16)
#define LCD_EN          (1 << 18)
#define LCD_D4          (1 << 19)
#define LCD_D5          (1 << 20)
#define LCD_D6          (1 << 21)
#define LCD_D7          (1 << 22)

#define LCD_DATA_MASK   (LCD_D4 | LCD_D5 | LCD_D6 | LCD_D7)

/* ADC Channel Definitions */
#define CH_TEMP         1
#define CH_LDR          2
#define CH_SOIL         3

/* Sensor Thresholds */
#define TEMP_HOT_C      40.0
#define LDR_DARK_RAW    300
#define SOIL_DRY_PCT    30

/* Delay Function */
void delay_ms(unsigned int ms);

/* GPIO Initialization */
void gpio_init(void);

/* UART0 Functions */
void uart0_init(void);
void uart0_send_char(char c);
void uart0_send_string(char *str);

/* ADC Functions */
void adc_init(void);
unsigned int adc_read(unsigned char channel);

/* Sensor Functions */
float temp_convert(unsigned int adc_val);
unsigned int ldr_read(void);
unsigned int soil_read_percent(void);
unsigned char water_read(void);

/* LCD Functions */
void lcd_pulse_enable(void);
void lcd_write_nibble(unsigned char nibble);
void lcd_cmd(unsigned char cmd);
void lcd_data(unsigned char data);
void lcd_string(char *str);
void lcd_init(void);
void lcd_set_cursor(unsigned char row, unsigned char col);

/* Output Helper Functions */
void print_uint(void (*out)(char), unsigned int n);
void lcd_out_char(char c);
void uart_out_char(char c);

/* LED Status Function */
void led_update(unsigned char alert, unsigned char warning);




