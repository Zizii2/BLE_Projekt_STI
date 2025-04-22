#pragma once

#include "driver/gpio.h"

typedef struct {
    gpio_num_t trig_pin;
    gpio_num_t echo_pin;
} ultrasonic_config_t;

void ultrasonic_init(ultrasonic_config_t *sensor);
float ultrasonic_measure();
