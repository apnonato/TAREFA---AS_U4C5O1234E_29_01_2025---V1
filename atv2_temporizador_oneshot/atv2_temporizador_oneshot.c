#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

#define BUTTON_PIN 5
#define LED1_PIN 11
#define LED2_PIN 12
#define LED3_PIN 13

volatile bool button_pressed = false;
volatile bool timer_running = false;
volatile uint8_t led_state = 0;

int64_t timer_callback(alarm_id_t id, void *user_data) {
    if (led_state == 0) {
        gpio_put(LED1_PIN, 0);
        gpio_put(LED2_PIN, 1);
        gpio_put(LED3_PIN, 1);
        led_state = 1;
    } else if (led_state == 1) {
        gpio_put(LED1_PIN, 0);
        gpio_put(LED2_PIN, 0);
        gpio_put(LED3_PIN, 1);
        led_state = 2;
    } else if (led_state == 2) {
        gpio_put(LED1_PIN, 0);
        gpio_put(LED2_PIN, 0);
        gpio_put(LED3_PIN, 0);
        led_state = 0;
        timer_running = false;
    }

    if (timer_running) {
        add_alarm_in_ms(3000, timer_callback, NULL, false);
    }
    return 0;
}

void button_callback(uint gpio, uint32_t events) {
    if (!timer_running && gpio == BUTTON_PIN) {
        button_pressed = true;
    }
}

bool debounce_button() {
    static uint32_t last_time = 0;
    uint32_t current_time = to_ms_since_boot(get_absolute_time());
    if (current_time - last_time > 50) {
        last_time = current_time;
        return true;
    }
    return false;
}

int main() {
    stdio_init_all();

    gpio_init(LED1_PIN);
    gpio_init(LED2_PIN);
    gpio_init(LED3_PIN);

    gpio_set_dir(LED1_PIN, GPIO_OUT);
    gpio_set_dir(LED2_PIN, GPIO_OUT);
    gpio_set_dir(LED3_PIN, GPIO_OUT);

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    gpio_set_irq_enabled_with_callback(BUTTON_PIN, GPIO_IRQ_EDGE_FALL, true, &button_callback);

    while (true) {
        if (button_pressed && !timer_running && debounce_button()) {
            button_pressed = false;
            timer_running = true;
            gpio_put(LED1_PIN, 1);
            gpio_put(LED2_PIN, 1);
            gpio_put(LED3_PIN, 1);
            add_alarm_in_ms(3000, timer_callback, NULL, false);
        }
        sleep_ms(100);
    }
}