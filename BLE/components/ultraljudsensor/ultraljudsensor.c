#include "ultraljudsensor.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"
#include "esp_log.h"

static const char *TAG = "HC-SR04";
static ultrasonic_config_t *sensor_config;

void ultrasonic_init(ultrasonic_config_t *sensor) {
    sensor_config = sensor;

    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << sensor_config->trig_pin),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_conf);
    gpio_set_level(sensor_config->trig_pin, 0);

    io_conf.pin_bit_mask = (1ULL << sensor_config->echo_pin);
    io_conf.mode = GPIO_MODE_INPUT;
    gpio_config(&io_conf);
}

float ultrasonic_measure() {
    gpio_set_level(sensor_config->trig_pin, 0);
    vTaskDelay(pdMS_TO_TICKS(2));  

    gpio_set_level(sensor_config->trig_pin, 1);
    esp_rom_delay_us(10);
    gpio_set_level(sensor_config->trig_pin, 0);

    int64_t start_time = 0, end_time = 0;
    int timeout = 1000000;

    while (gpio_get_level(sensor_config->echo_pin) == 0 && timeout > 0) {
        start_time = esp_timer_get_time();
        timeout--;
    }
    if (timeout == 0) return -1.0;

    timeout = 1000000;
    while (gpio_get_level(sensor_config->echo_pin) == 1 && timeout > 0) {
        end_time = esp_timer_get_time();
        timeout--;
    }
    if (timeout == 0) return -1.0;

    int64_t duration = end_time - start_time;
    float distance = (duration / 2.0) * 0.0343;
    
    
    return distance;
}