#include "nvs.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "esp_log.h"

#define NAMESPACE "storage"

esp_err_t nvs_helper_write_i32(const char* key, int32_t value) {
    nvs_handle_t handle;
    esp_err_t err;

    err = nvs_open(NAMESPACE, NVS_READWRITE, &handle);
    if (err != ESP_OK) return err;

    err = nvs_set_i32(handle, key, value);
    if (err == ESP_OK) err = nvs_commit(handle);

    nvs_close(handle);
    return err;
}

esp_err_t nvs_helper_read_i32(const char* key, int32_t* out_value) {
    nvs_handle_t handle;
    esp_err_t err;

    err = nvs_open(NAMESPACE, NVS_READONLY, &handle);
    if (err != ESP_OK) return err;

    err = nvs_get_i32(handle, key, out_value);
    nvs_close(handle);
    return err;
}
