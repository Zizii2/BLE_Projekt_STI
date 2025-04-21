#pragma once
#include "esp_err.h"

esp_err_t nvs_helper_write_i32(const char* key, int32_t value);
esp_err_t nvs_helper_read_i32(const char* key, int32_t* out_value);



