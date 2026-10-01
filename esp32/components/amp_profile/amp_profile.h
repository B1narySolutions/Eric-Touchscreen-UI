#pragma once
#include "lvgl.h"

/* All timing hooks are ESP32-only; generated UI and desktop preview stay intact. */
void amp_profile_attach(lv_display_t *display, lv_indev_t *touch);
void amp_profile_start(void);
