file(GLOB_RECURSE srcs "main.c" "src/*.c")

idf_component_register(SRCS "${srcs}"
                       INCLUDE_DIRS "./include" "../components/ultraljudsensor/include"
                       REQUIRES driver bt esp_timer nvs_flash)
