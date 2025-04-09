#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/adc.h"
#include "ssd1306.h"
#include "pico/cyw43_arch.h"


#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGTH 64
#define SCREEN_ADDRESS 0x3C
#define I2C_SDA 14
#define I2C_SCL 15
#define ADC_Y 26
#define ADC_X 27
#define SSID "WIFI"
#define PASS "12345678"
#define ADC_MAX 4095

ssd1306_t display;

void loc_joystick(int x, int y){
    ssd1306_clear(&display);
    ssd1306_draw_string(&display, x, y, 1, "o");
    ssd1306_show(&display);
}

void setup(){
    stdio_init_all();

    i2c_init(i2c1, 400*1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    adc_init();
    adc_gpio_init(ADC_X);
    adc_gpio_init(ADC_Y);
 

    if (!ssd1306_init(&display, DISPLAY_WIDTH, DISPLAY_HEIGTH, SCREEN_ADDRESS, i2c1)) { 
        printf("Falha ao inicializar o display SSD1306\n");
    }


}

int main()
{
    setup();

    while (true) {
        adc_select_input(0);
        uint adc_y = adc_read(); 
        adc_select_input(1);   
        uint adc_x = adc_read();

        adc_y /= 63;
        adc_x /= 31;
        
        loc_joystick(adc_x, adc_y);

        sleep_ms(69);
    }
}
