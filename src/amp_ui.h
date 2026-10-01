#ifndef AMP_UI_H
#define AMP_UI_H
#include "lvgl.h"
void amp_ui_init(void);
/* Headless interaction checks; returns the number of failed checks. */
int amp_ui_smoke_test(void);
void amp_ui_preview_scene(int scene);
#endif
