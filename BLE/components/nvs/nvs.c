#include "nvs_storage.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "esp_log.h"

#define NVS_NAMESPACE "storage"
#define SENSOR_KEY "sensor_value"
using namespace std;


esp_err_t NVSStorage::init() {
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    return err;
}

esp_err_t NVSStorage::saveSensorData(int sensor_value) {
    nvs_handle_t my_handle;
    esp_err_t err = nvs_open(NVS_NAMESPACE, NVS_READWRITE, &my_handle);
    if (err != ESP_OK) {
        ESP_LOGE("NVS", "Error opening NVS handle!");
        return err;
    }

    err = nvs_set_i32(my_handle, SENSOR_KEY, sensor_value);
    if (err != ESP_OK) {
        ESP_LOGE("NVS", "Error saving sensor data to NVS");
    } else {
        err = nvs_commit(my_handle);  
    }

    nvs_close(my_handle);
    return err;
}
esp_err_t NVSStorage::readSensorData(int &sensor_value) {
    nvs_handle_t my_handle;
    esp_err_t err = nvs_open(NVS_NAMESPACE, NVS_READONLY, &my_handle);
    if (err != ESP_OK) {
        ESP_LOGE("NVS", "Error opening NVS handle!");
        return err;
    }

    err = nvs_get_i32(my_handle, SENSOR_KEY, &sensor_value);
    if (err != ESP_OK) {
        ESP_LOGE("NVS", "Error reading sensor data from NVS");
    }

    nvs_close(my_handle);
    return err;
}
