#include "amp_profile.h"
#include <inttypes.h>
#include <stdbool.h>
#include <string.h>
#include "esp_timer.h"
#include "esp_log.h"
#include "esp_heap_caps.h"
#include "esp_lcd_touch.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define REPORT_MS 5000
#define SLOW_US 16000
static const char *TAG = "amp_prof";
typedef enum {
    TIMER, TIMER_GAP, INPUT, TOUCH_READ, TOUCH_CALLBACK, TOUCH_GAP,
    LAYOUT, SUBJECT, PRESS, DRAG, RELEASE, CLICK, GESTURE, VALUE,
    CHAIN_DRAG, HOME_CREATE, REFRESH, RENDER, RENDER_WORK, FLUSH, FLUSH_WAIT,
    TOUCH_TO_RENDER, SECTION_COUNT
} section_t;
static const char *names[SECTION_COUNT] = {
    "lvgl.timer_handler", "lvgl.handler_interval", "input.process",
    "touch.gt911_read", "touch.adapter_read", "touch.poll_interval",
    "ui.layout", "ui.subject_update", "event.pressed", "event.pressing",
    "event.released", "event.clicked", "event.gesture", "event.value_changed",
    "chain.drag_handler", "startup.home_create", "display.refresh_cycle",
    "display.render", "display.render_excluding_flush", "display.flush_submit", "display.flush_wait",
    "touch.sample_to_render_ready"
};
typedef struct {
    uint64_t total;
    uint32_t count, maximum, slow;
} stats_t;
static stats_t stats[SECTION_COUNT];
static portMUX_TYPE stats_mux = portMUX_INITIALIZER_UNLOCKED;
static lv_indev_read_cb_t original_touch_read;
static int64_t previous_handler, previous_touch;
static int64_t refresh_start, render_start, flush_start, wait_start;
static int64_t render_flush_us;
static bool rendered_this_cycle;
static int64_t pending_touch;
static bool last_pressed;
static lv_point_t last_point;
static uint32_t pressed_samples, moved_samples;
typedef struct {
    lv_obj_t *obj;
    int32_t x, y;
} position_watch_t;
static position_watch_t position_watch[32];
static uint32_t geometry_checks, geometry_changes;
static char geometry_last[64];

static void watch_position(lv_obj_t *obj, const char *name)
{
    if(!obj || lv_obj_has_flag(obj, LV_OBJ_FLAG_HIDDEN)) return;
    int32_t x = lv_obj_get_x(obj), y = lv_obj_get_y(obj);
    for(unsigned i = 0; i < 32; i++) {
        position_watch_t *w = &position_watch[i];
        if(!w->obj) { *w = (position_watch_t){obj, x, y}; return; }
        if(w->obj != obj) continue;
        portENTER_CRITICAL(&stats_mux);
        geometry_checks++;
        if(w->x != x || w->y != y) {
            geometry_changes++;
            strncpy(geometry_last, name, sizeof(geometry_last) - 1);
        }
        portEXIT_CRITICAL(&stats_mux);
        w->x = x; w->y = y;
        return;
    }
}

static void check_geometry(void)
{
    static const char *blocks[] = {"gate_block", "comp_block", "drive_block", "amp_block",
                                 "chorus_block", "delay_block", "reverb_block", "cabinet_block"};
    static const char *editors[] = {"gate_editor", "comp_editor", "drive_editor", "amp_editor",
                                  "chorus_editor", "delay_editor", "reverb_editor", "cabinet_editor"};
    lv_obj_t *screen = lv_screen_active();
    for(unsigned i = 0; i < 8; i++) {
        watch_position(lv_obj_find_by_name(screen, editors[i]), editors[i]);
        lv_obj_t *block = lv_obj_find_by_name(screen, blocks[i]);
        if(!block || lv_obj_get_child_count(block) < 2) continue;
        lv_obj_t *toggle = lv_obj_get_child(block, 1);
        watch_position(toggle, blocks[i]);
        /* Child 0 is the empty amp_button label; 1/2 are ON/BYPASS. */
        for(unsigned j = 1; j < lv_obj_get_child_count(toggle); j++)
            watch_position(lv_obj_get_child(toggle, j), blocks[i]);
    }
}

static void record(section_t section, int64_t elapsed)
{
    if(elapsed < 0) return;
    uint32_t us = elapsed > UINT32_MAX ? UINT32_MAX : (uint32_t)elapsed;
    portENTER_CRITICAL(&stats_mux);
    stats_t *s = &stats[section];
    s->count++;
    s->total += us;
    if(us > s->maximum) s->maximum = us;
    if(us >= SLOW_US) s->slow++;
    portEXIT_CRITICAL(&stats_mux);
}

uint32_t __real_lv_timer_handler(void);
uint32_t __wrap_lv_timer_handler(void)
{
    int64_t start = esp_timer_get_time();
    if(previous_handler) record(TIMER_GAP, start - previous_handler);
    previous_handler = start;
    uint32_t result = __real_lv_timer_handler();
    record(TIMER, esp_timer_get_time() - start);
    return result;
}

static void input_timer(lv_timer_t *timer)
{
    int64_t start = esp_timer_get_time();
    lv_indev_read_timer_cb(timer);
    record(INPUT, esp_timer_get_time() - start);
}

esp_err_t __real_esp_lcd_touch_read_data(esp_lcd_touch_handle_t touch);
esp_err_t __wrap_esp_lcd_touch_read_data(esp_lcd_touch_handle_t touch)
{
    int64_t start = esp_timer_get_time();
    esp_err_t result = __real_esp_lcd_touch_read_data(touch);
    record(TOUCH_READ, esp_timer_get_time() - start);
    return result;
}

void __real_lv_obj_update_layout(const lv_obj_t *obj);
void __wrap_lv_obj_update_layout(const lv_obj_t *obj)
{
    int64_t start = esp_timer_get_time();
    __real_lv_obj_update_layout(obj);
    record(LAYOUT, esp_timer_get_time() - start);
}

void __real_lv_subject_set_int(lv_subject_t *subject, int32_t value);
void __wrap_lv_subject_set_int(lv_subject_t *subject, int32_t value)
{
    int64_t start = esp_timer_get_time();
    __real_lv_subject_set_int(subject, value);
    record(SUBJECT, esp_timer_get_time() - start);
}

lv_result_t __real_lv_obj_send_event(lv_obj_t *obj, lv_event_code_t code, void *param);
lv_result_t __wrap_lv_obj_send_event(lv_obj_t *obj, lv_event_code_t code, void *param)
{
    section_t section;
    switch(code) {
        case LV_EVENT_PRESSED: section = PRESS; break;
        case LV_EVENT_PRESSING: section = DRAG; break;
        case LV_EVENT_RELEASED: case LV_EVENT_PRESS_LOST: section = RELEASE; break;
        case LV_EVENT_CLICKED: case LV_EVENT_SHORT_CLICKED: section = CLICK; break;
        case LV_EVENT_GESTURE: section = GESTURE; break;
        case LV_EVENT_VALUE_CHANGED: section = VALUE; break;
        default: return __real_lv_obj_send_event(obj, code, param);
    }
    int64_t start = esp_timer_get_time();
    lv_result_t result = __real_lv_obj_send_event(obj, code, param);
    record(section, esp_timer_get_time() - start);
    return result;
}

void __real_amp_chain_drag_event(lv_event_t *event);
void __wrap_amp_chain_drag_event(lv_event_t *event)
{
    int64_t start = esp_timer_get_time();
    __real_amp_chain_drag_event(event);
    record(CHAIN_DRAG, esp_timer_get_time() - start);
}

lv_obj_t *__real_home_create(void);
lv_obj_t *__wrap_home_create(void)
{
    int64_t start = esp_timer_get_time();
    lv_obj_t *result = __real_home_create();
    record(HOME_CREATE, esp_timer_get_time() - start);
    return result;
}

static void touch_read(lv_indev_t *indev, lv_indev_data_t *data)
{
    int64_t start = esp_timer_get_time();
    if(previous_touch) record(TOUCH_GAP, start - previous_touch);
    previous_touch = start;
    original_touch_read(indev, data);
    int64_t end = esp_timer_get_time();
    record(TOUCH_CALLBACK, end - start);
    bool pressed = data->state == LV_INDEV_STATE_PRESSED;
    bool moved = pressed && (!last_pressed || data->point.x != last_point.x ||
                            data->point.y != last_point.y);
    if(pressed) {
        portENTER_CRITICAL(&stats_mux);
        pressed_samples++;
        if(moved) moved_samples++;
        portEXIT_CRITICAL(&stats_mux);
    }
    /* Keep the oldest unrendered sample; do not hide stalls with newer samples. */
    if((moved || pressed != last_pressed) && !pending_touch) pending_touch = end;
    last_pressed = pressed;
    last_point = data->point;
}

static void display_event(lv_event_t *event)
{
    int64_t now = esp_timer_get_time();
    switch(lv_event_get_code(event)) {
        case LV_EVENT_REFR_START:
            refresh_start = now;
            rendered_this_cycle = false;
            break;
        case LV_EVENT_REFR_READY:
            if(refresh_start) record(REFRESH, now - refresh_start);
            if(rendered_this_cycle) check_geometry();
            /* A touch with no redraw must not contaminate a later interaction. */
            if(!rendered_this_cycle) pending_touch = 0;
            refresh_start = 0; break;
        case LV_EVENT_RENDER_START:
            render_start = now;
            render_flush_us = 0;
            rendered_this_cycle = true;
            break;
        case LV_EVENT_RENDER_READY:
            if(render_start) {
                record(RENDER, now - render_start);
                record(RENDER_WORK, now - render_start - render_flush_us);
            }
            render_start = 0;
            if(pending_touch) {
                record(TOUCH_TO_RENDER, now - pending_touch);
                pending_touch = 0;
            }
            break;
        case LV_EVENT_FLUSH_START: flush_start = now; break;
        case LV_EVENT_FLUSH_FINISH:
            if(flush_start) {
                record(FLUSH, now - flush_start);
                if(render_start) render_flush_us += now - flush_start;
            }
            flush_start = 0; break;
        case LV_EVENT_FLUSH_WAIT_START: wait_start = now; break;
        case LV_EVENT_FLUSH_WAIT_FINISH:
            if(wait_start) record(FLUSH_WAIT, now - wait_start);
            wait_start = 0; break;
        default: break;
    }
}

void amp_profile_attach(lv_display_t *display, lv_indev_t *touch)
{
    lv_display_add_event_cb(display, display_event, LV_EVENT_ALL, NULL);
    if(touch) {
        original_touch_read = lv_indev_get_read_cb(touch);
        if(original_touch_read) lv_indev_set_read_cb(touch, touch_read);
        lv_timer_t *timer = lv_indev_get_read_timer(touch);
        if(timer) lv_timer_set_cb(timer, input_timer);
    }
}

static void report_task(void *arg)
{
    (void)arg;
    stats_t snapshot[SECTION_COUNT];
    for(;;) {
        vTaskDelay(pdMS_TO_TICKS(REPORT_MS));
        portENTER_CRITICAL(&stats_mux);
        memcpy(snapshot, stats, sizeof(snapshot));
        memset(stats, 0, sizeof(stats));
        uint32_t pressed = pressed_samples, moved = moved_samples;
        uint32_t checks = geometry_checks, changes = geometry_changes;
        char last[64];
        memcpy(last, geometry_last, sizeof(last));
        geometry_checks = geometry_changes = 0;
        pressed_samples = moved_samples = 0;
        portEXIT_CRITICAL(&stats_mux);
        ESP_LOGI(TAG, "--- 5s window; inclusive times overlap; slow >=16ms ---");
        for(unsigned i = 0; i < SECTION_COUNT; i++) {
            stats_t *s = &snapshot[i];
            if(!s->count) continue;
            ESP_LOGI(TAG, "%s n=%" PRIu32 " avg=%.3fms max=%.3fms total=%.1fms slow=%" PRIu32,
                     names[i], s->count, (double)s->total / s->count / 1000.0,
                     s->maximum / 1000.0, s->total / 1000.0, s->slow);
        }
        ESP_LOGI(TAG, "touch pressed=%" PRIu32 " moved=%" PRIu32
                 "; render_rate=%.1f/s; free SRAM=%u PSRAM=%u; largest SRAM=%u",
                 pressed, moved, snapshot[RENDER].count / (REPORT_MS / 1000.0),
                 (unsigned)heap_caps_get_free_size(MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT),
                 (unsigned)heap_caps_get_free_size(MALLOC_CAP_SPIRAM),
                 (unsigned)heap_caps_get_largest_free_block(MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT));
        ESP_LOGI(TAG, "geometry checks=%" PRIu32 " position_changes=%" PRIu32 " last=%s",
                 checks, changes, changes ? last : "none");
    }
}

void amp_profile_start(void)
{
    ESP_LOGI(TAG, "Enabled: 22 timing sections; summaries every %dms", REPORT_MS);
    ESP_LOGI(TAG, "sample_to_render_ready is a software proxy, not physical touch-to-photon latency");
    BaseType_t result = xTaskCreate(report_task, "amp_profile", 4096, NULL, 1, NULL);
    configASSERT(result == pdPASS);
}
