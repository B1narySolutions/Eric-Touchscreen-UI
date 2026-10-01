idf_component_register(
    SRCS "main.c" "lvgl_fs.c"
    INCLUDE_DIRS "."
    REQUIRES amp_profile amp_ui rgb_lcd_port spiffs esp_lvgl_adapter
)

spiffs_create_partition_image(storage assets FLASH_IN_PROJECT)

idf_component_get_property(lvgl_lib lvgl__lvgl COMPONENT_LIB)
target_compile_options(${lvgl_lib} PRIVATE -Wno-format)
