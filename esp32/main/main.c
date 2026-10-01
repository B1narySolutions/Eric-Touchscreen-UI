#include <assert.h>

#include "esp_heap_caps.h"
#include "esp_log.h"
#include "esp_lv_adapter.h"
#include "lvgl.h"

#include "amp_editor.h"
#include "amp_profile.h"
#include "lvgl_fs.h"
#include "rgb_lcd_port.h"

static const char * TAG = "amp_display";

void app_main(void)
{
    const esp_lv_adapter_rotation_t rotation = ESP_LV_ADAPTER_ROTATE_0;
    const esp_lv_adapter_tear_avoid_mode_t tear_mode = ESP_LV_ADAPTER_TEAR_AVOID_MODE_DOUBLE_DIRECT;
    esp_lcd_panel_handle_t panel = NULL;
    esp_lcd_touch_handle_t touch_panel = NULL;

    ESP_LOGI(TAG, "Starting Waveshare ESP32-S3-Touch-LCD-7B UI");
    ESP_LOGI(TAG, "PSRAM available: %u bytes",
             (unsigned)heap_caps_get_free_size(MALLOC_CAP_SPIRAM));

    ESP_ERROR_CHECK(waveshare_esp32_s3_rgb_lcd_init(
        tear_mode, rotation, &panel, &touch_panel));

    esp_lv_adapter_config_t adapter_config = ESP_LV_ADAPTER_DEFAULT_CONFIG();
    adapter_config.task_stack_size = 16 * 1024;
    adapter_config.stack_in_psram = true;
    ESP_ERROR_CHECK(esp_lv_adapter_init(&adapter_config));

    esp_lv_adapter_display_config_t display_config = ESP_LV_ADAPTER_DISPLAY_RGB_DEFAULT_CONFIG(
        panel, NULL, EXAMPLE_LCD_H_RES, EXAMPLE_LCD_V_RES, rotation);
    /* Draw dirty regions directly into the panel's two full-size buffers.
     * Avoid the partial adapter path copying unchanged screen regions each frame. */
    display_config.tear_avoid_mode = tear_mode;
    display_config.profile.buffer_height = EXAMPLE_LCD_V_RES;
    display_config.profile.use_psram = true;
    ESP_LOGI(TAG, "Display mode: DOUBLE_DIRECT, 2 panel framebuffers");

    lv_display_t * display = esp_lv_adapter_register_display(&display_config);
    assert(display != NULL);

    lv_indev_t *touch = NULL;
    if(touch_panel != NULL) {
        esp_lv_adapter_touch_config_t touch_config =
            ESP_LV_ADAPTER_TOUCH_DEFAULT_CONFIG(display, touch_panel);
        touch = esp_lv_adapter_register_touch(&touch_config);
        assert(touch != NULL);
    }

    amp_profile_attach(display, touch);
    ESP_ERROR_CHECK(amp_lvgl_fs_init());
    ESP_ERROR_CHECK(esp_lv_adapter_start());

    ESP_ERROR_CHECK(esp_lv_adapter_lock(-1));
    amp_editor_init("S:/");
    lv_screen_load(home_create());
    esp_lv_adapter_unlock();

    wavesahre_rgb_lcd_bl_on();
    ESP_LOGI(TAG, "Amplifier UI ready");
}
