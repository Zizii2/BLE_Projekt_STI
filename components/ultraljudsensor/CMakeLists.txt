idf_component_register(SRCS "ultraljudsensor.c"
                    INCLUDE_DIRS "include"
                    REQUIRES driver
                    REQUIRES driver freertos
                    REQUIRES esp_timer)
