#ifndef NVS_STORAGE_H
#define NVS_STORAGE_H

#include "esp_err.h"

class NVSStorage {
public:
    static esp_err_t init();
    static esp_err_t saveSensorData(int sensor_value);
    static esp_err_t readSensorData(int &sensor_value);
};

#endif 

