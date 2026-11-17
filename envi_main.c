
#include<lpc21xx.h>
#include"header.h"
int main(void)
{
    unsigned int temp_adc, ldr_raw, soil_pct;
    float temperature;
    unsigned char water;
    unsigned char alert, warning;
    char *status;
    char *light_level;
   // char *soil_level;

    gpio_init();
    uart0_init();
    adc_init();
    lcd_init();

    lcd_string("Env Monitor");
    delay_ms(1000);
    lcd_cmd(0x01);

    while (1)
    {
        /* ---- Step 1: Read all sensors ---- */
        temp_adc = adc_read(CH_TEMP);
        temperature = temp_convert(temp_adc);
        ldr_raw = ldr_read();
        soil_pct = soil_read_percent();
        water = water_read();
        
			   
        /* ---- Step 2: Classify each reading ---- */
        light_level = (ldr_raw < LDR_DARK_RAW) ? "DARK" : "NORMAL";
     //   soil_level  = (soil_pct < SOIL_DRY_PCT) ? "DRY" : "OK";

        /* ---- Step 3: Decide overall status ----
           WHY this priority: water = immediate hazard (ALERT/RED).
           Any other single abnormal reading = WARNING (YELLOW).
           All normal = SAFE (GREEN). */
        alert = water;
        warning = (!alert) && (temperature > TEMP_HOT_C ||
                                ldr_raw < LDR_DARK_RAW ||
                                soil_pct < SOIL_DRY_PCT);

        if (alert)
            status = "ALERT";
        else if (temperature > TEMP_HOT_C)
            status = "HOT";
        else if (ldr_raw < LDR_DARK_RAW)
            status = "DARK";
        else if (soil_pct < SOIL_DRY_PCT)
            status = "WATER";   //  dry soil -> "Status: WATER" (needs watering)
        else
            status = "SAFE";

        /* ---- Step 4: LCD output ---- */
        int t_int = (int)temperature;
        int t_dec = (int)((temperature - t_int) * 10);

        lcd_set_cursor(0, 0);
        lcd_string("T:");
        print_uint(lcd_out_char, (unsigned int)t_int);
        lcd_data('.'); lcd_data('0' + t_dec); lcd_data(0xDF); lcd_data('C');
        lcd_string(" S:");
        lcd_string(status);

        lcd_set_cursor(1, 0);
        lcd_string("Soil:");
        print_uint(lcd_out_char, soil_pct);
        lcd_string("% ");
        lcd_string(light_level);

        /* ---- Step 5: LED output ---- */
        led_update(alert, warning);

        /* ---- Step 6: UART output ---- */
        uart0_send_string("Temperature   : ");
        print_uint(uart_out_char, (unsigned int)t_int);
        uart0_send_string(".");
        uart0_send_char('0' + t_dec);
        uart0_send_string(" C\r\n");

        uart0_send_string("Light Level   : ");
        uart0_send_string(light_level);
        uart0_send_string("\r\n");

        uart0_send_string("Soil Moisture : ");
        print_uint(uart_out_char, soil_pct);
        uart0_send_string(" %\r\n");

        uart0_send_string("Water Sensor  : ");
        uart0_send_string(water ? "DETECTED\r\n" : "NOT DETECTED\r\n");

        uart0_send_string("System Status : ");
        uart0_send_string(status);
        uart0_send_string("\r\n\r\n");

        delay_ms(1000);   
    }
}




