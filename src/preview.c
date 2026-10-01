/* Headless rendering and interaction checks using the actual LVGL widgets. */
#include "amp_ui.h"
#include <stdio.h>
static void flush(lv_display_t *display, const lv_area_t *area, uint8_t *pixels)
{
    (void)area; (void)pixels; lv_display_flush_ready(display);
}
static int snapshot(const char *path)
{
    lv_obj_update_layout(lv_screen_active());
    lv_draw_buf_t *buf = lv_snapshot_take(lv_screen_active(), LV_COLOR_FORMAT_RGB888);
    if(!buf) return 1;
    FILE *file = fopen(path, "wb");
    if(!file) { lv_draw_buf_destroy(buf); return 1; }
    fprintf(file, "P6\n%u %u\n255\n", (unsigned)buf->header.w, (unsigned)buf->header.h);
    for(unsigned y = 0; y < buf->header.h; y++) {
        const uint8_t *row = buf->data + y * buf->header.stride;
        for(unsigned x = 0; x < buf->header.w; x++) {
            uint8_t rgb[3] = {row[x * 3 + 2], row[x * 3 + 1], row[x * 3]};
            fwrite(rgb, 1, 3, file);
        }
    }
    int failed = ferror(file); fclose(file); lv_draw_buf_destroy(buf); return failed;
}
int amp_preview(const char *path, int scene)
{
    lv_init(); lv_lock();
    lv_display_t *display = lv_display_create(1024, 600);
    static uint8_t pixels[1024 * 40 * 4];
    lv_display_set_buffers(display, pixels, NULL, sizeof(pixels), LV_DISPLAY_RENDER_MODE_PARTIAL);
    lv_display_set_flush_cb(display, flush);
    amp_ui_init();
    int result = amp_ui_smoke_test();
    amp_ui_preview_scene(scene);
    if(path) result += snapshot(path);
    lv_unlock(); lv_deinit(); return result ? 1 : 0;
}
