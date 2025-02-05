#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

#define LED_RED_PIN 11
#define LED_YELLOW_PIN 12
#define LED_GREEN_PIN 13

volatile uint8_t traffic_light_state = 0;

bool traffic_light_timer_callback(struct repeating_timer *t) {
    if (traffic_light_state == 0) {
        gpio_put(LED_RED_PIN, 0);
        gpio_put(LED_YELLOW_PIN, 1);
        gpio_put(LED_GREEN_PIN, 0);
        traffic_light_state = 1;
    } else if (traffic_light_state == 1) {
        gpio_put(LED_RED_PIN, 0);
        gpio_put(LED_YELLOW_PIN, 0);
        gpio_put(LED_GREEN_PIN, 1);
        traffic_light_state = 2;
    } else if (traffic_light_state == 2) {
        gpio_put(LED_RED_PIN, 1);
        gpio_put(LED_YELLOW_PIN, 0);
        gpio_put(LED_GREEN_PIN, 0);
        traffic_light_state = 0;
    }
    return true;
}

int main() {
    stdio_init_all();

    gpio_init(LED_RED_PIN);
    gpio_init(LED_YELLOW_PIN);
    gpio_init(LED_GREEN_PIN);

    gpio_set_dir(LED_RED_PIN, GPIO_OUT);
    gpio_set_dir(LED_YELLOW_PIN, GPIO_OUT);
    gpio_set_dir(LED_GREEN_PIN, GPIO_OUT);

    gpio_put(LED_RED_PIN, 1);
    gpio_put(LED_YELLOW_PIN, 0);
    gpio_put(LED_GREEN_PIN, 0);

    struct repeating_timer traffic_light_timer;
    add_repeating_timer_ms(3000, traffic_light_timer_callback, NULL, &traffic_light_timer);

    while (true) {
        sleep_ms(1000);
    }
}