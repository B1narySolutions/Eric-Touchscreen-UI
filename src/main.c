/**
 * @file main.c
 *
 * Minimal LVGL PC simulator.
 */

#include "lvgl.h"
#include "hal.h"
#include "amp_ui.h"
#include <string.h>
#include <stdlib.h>
int amp_preview(const char *path, int scene);

#if HAS_UI
/* Header exported by the LVGL Editor into the ui/ folder. */
#include "ui/amp_editor.h"
#endif

#ifdef _WIN32
#include <windows.h>
static void msleep(uint32_t ms) { Sleep(ms); }
#else
#include <unistd.h>
static void msleep(uint32_t ms) { usleep(ms * 1000); }
#endif

int main(int argc, char **argv)
{
    if(argc > 1 && strcmp(argv[1], "--check") == 0)
        return amp_preview(argc > 2 ? argv[2] : NULL, argc > 3 ? atoi(argv[3]) : 0);
    /*Initialize LVGL*/
    lv_init();

    /* The Windows creation thread needs LVGL's mutex during WM_CREATE.
     * Do not hold that mutex while waiting for the display to be created. */
    hal_init(1024, 600);

    lv_lock();
#if HAS_UI
    amp_editor_init("A:ui");
    lv_screen_load(home_create());
#else
    amp_ui_init();
#endif

    lv_unlock();

    /*Handle LVGL tasks until the window is closed*/
    while(1) {
        lv_lock();
        bool window_open = lv_display_get_default() != NULL;
        lv_unlock();
        if(!window_open) break;
        uint32_t idle_ms = lv_timer_handler();
        if(idle_ms == LV_NO_TIMER_READY || idle_ms > 20) {
            idle_ms = 20;
        }
        msleep(idle_ms);
    }

    return 0;
}
