idf_component_register(SRCS "amp_profile.c" INCLUDE_DIRS "."
    REQUIRES lvgl__lvgl esp_timer esp_lcd_touch heap freertos)

# Link-time hooks avoid editing generated UI or managed dependency sources.
foreach(symbol lv_timer_handler esp_lcd_touch_read_data
        lv_obj_update_layout lv_subject_set_int lv_obj_send_event
        amp_chain_drag_event home_create)
    target_link_libraries(${COMPONENT_LIB} INTERFACE "-Wl,--wrap=${symbol}")
endforeach()
