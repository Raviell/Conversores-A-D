#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"
#include "hardware/i2c.h"
#include "ssd1306.h"

#define JOY_X 26
#define JOY_Y 27
#define LED_R 11
#define LED_G 12
#define LED_B 13
#define BTN_JOY 22
#define BTN_A 5
#define I2C_SDA 14
#define I2C_SCL 15

volatile bool toggle_led_g = false;
volatile bool toggle_pwm = true;

void irq_btn_joy(uint gpio, uint32_t events) {
    toggle_led_g = !toggle_led_g;
    gpio_put(LED_G, toggle_led_g);
}

void irq_btn_a(uint gpio, uint32_t events) {
    toggle_pwm = !toggle_pwm;
}

void setup_pwm(uint pin) {
    gpio_set_function(pin, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(pin);
    pwm_set_wrap(slice, 4095);
    pwm_set_enabled(slice, true);
}

void update_leds(uint16_t joy_x, uint16_t joy_y) {
    uint slice_r = pwm_gpio_to_slice_num(LED_R);
    uint slice_b = pwm_gpio_to_slice_num(LED_B);
    if (toggle_pwm) {
        pwm_set_gpio_level(LED_R, abs(joy_x - 2048));
        pwm_set_gpio_level(LED_B, abs(joy_y - 2048));
    } else {
        pwm_set_gpio_level(LED_R, 0);
        pwm_set_gpio_level(LED_B, 0);
    }
}

void setup() {
    stdio_init_all();
    adc_init();
    adc_gpio_init(JOY_X);
    adc_gpio_init(JOY_Y);
    gpio_init(LED_G);
    gpio_set_dir(LED_G, GPIO_OUT);
    gpio_init(BTN_JOY);
    gpio_set_dir(BTN_JOY, GPIO_IN);
    gpio_pull_up(BTN_JOY);
    gpio_set_irq_enabled_with_callback(BTN_JOY, GPIO_IRQ_EDGE_FALL, true, &irq_btn_joy);
    gpio_init(BTN_A);
    gpio_set_dir(BTN_A, GPIO_IN);
    gpio_pull_up(BTN_A);
    gpio_set_irq_enabled_with_callback(BTN_A, GPIO_IRQ_EDGE_FALL, true, &irq_btn_a);
    setup_pwm(LED_R);
    setup_pwm(LED_B);
    i2c_init(i2c0, 400 * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
    ssd1306_init();
}

int main() {
    setup();
    while (1) {
        adc_select_input(0);
        uint16_t joy_x = adc_read();
        adc_select_input(1);
        uint16_t joy_y = adc_read();
        update_leds(joy_x, joy_y);
        ssd1306_draw_square(joy_x / 512, joy_y / 512, 8, 8);
        sleep_ms(50);
    }
}
