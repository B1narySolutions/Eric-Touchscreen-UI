#include "amp_ui.h"
#include "amp_model.h"
#include <stdint.h>
#include <stdio.h>

#define BG 0x111416
#define PANEL 0x1B2023
#define EDGE 0x343C40
#define INK 0xF2EEE6
#define MUTED 0xA0AAAE
#define AMBER 0xE9B76E

static amp_tone_t tone, saved[3];
static int preset, selected = AMP_AMP, master = 65, aux = 35;
static bool muted, headphones;
static lv_obj_t *root, *editor, *preset_label, *dirty_label, *toast_label, *volume_label;
static lv_obj_t *select_buttons[7], *bypass_buttons[7], *bypass_labels[7];
static lv_obj_t *arcs[5], *values[5], *voice_buttons[3], *master_slider, *mute_button;
static lv_obj_t *modal, *load_buttons[3], *save_button;
static lv_timer_t *toast_timer;

static lv_color_t color(unsigned c) { return lv_color_hex(c); }
static lv_obj_t *box(lv_obj_t *parent, int x, int y, int w, int h, unsigned bg)
{
    lv_obj_t *o = lv_obj_create(parent);
    lv_obj_remove_style_all(o);
    lv_obj_set_pos(o, x, y); lv_obj_set_size(o, w, h);
    lv_obj_set_style_bg_color(o, color(bg), 0); lv_obj_set_style_bg_opa(o, LV_OPA_COVER, 0);
    lv_obj_set_style_radius(o, 16, 0);
    lv_obj_remove_flag(o, LV_OBJ_FLAG_SCROLLABLE);
    return o;
}
static lv_obj_t *label(lv_obj_t *parent, const char *text, int x, int y, unsigned c, const lv_font_t *font)
{
    lv_obj_t *o = lv_label_create(parent);
    lv_label_set_text(o, text); lv_obj_set_pos(o, x, y);
    lv_obj_set_style_text_color(o, color(c), 0); lv_obj_set_style_text_font(o, font, 0);
    return o;
}
static lv_obj_t *button(lv_obj_t *parent, const char *text, int x, int y, int w, int h, unsigned bg, lv_event_cb_t cb, intptr_t id)
{
    lv_obj_t *b = lv_button_create(parent);
    lv_obj_remove_style_all(b); lv_obj_set_pos(b, x, y); lv_obj_set_size(b, w, h);
    lv_obj_set_style_bg_color(b, color(bg), 0); lv_obj_set_style_bg_opa(b, LV_OPA_COVER, 0);
    lv_obj_set_style_radius(b, 10, 0); lv_obj_set_style_border_color(b, color(EDGE), 0);
    lv_obj_set_style_border_width(b, 1, 0);
    lv_obj_set_style_bg_color(b, color(0x434B50), LV_STATE_PRESSED);
    lv_obj_t *t = label(b, text, 0, 0, INK, &lv_font_montserrat_16); lv_obj_center(t);
    if(cb) lv_obj_add_event_cb(b, cb, LV_EVENT_CLICKED, (void *)id);
    return b;
}
static void dirty_update(void)
{
    bool dirty = !amp_tone_equal(&tone, &saved[preset]);
    lv_label_set_text(dirty_label, dirty ? "EDITED" : "SAVED");
    lv_obj_set_style_text_color(dirty_label, color(dirty ? AMBER : MUTED), 0);
}
static void toast_clear(lv_timer_t *timer) { (void)timer; lv_label_set_text(toast_label, ""); }
static void toast(const char *text)
{
    lv_label_set_text(toast_label, text);
    lv_timer_reset(toast_timer); lv_timer_resume(toast_timer);
}
static void build_editor(void);
static void refresh_chain(void)
{
    for(int i = 0; i < AMP_BLOCK_COUNT; i++) {
        unsigned accent = amp_blocks[i].color;
        lv_obj_set_style_border_color(select_buttons[i], color(i == selected ? accent : EDGE), 0);
        lv_obj_set_style_border_width(select_buttons[i], i == selected ? 2 : 1, 0);
        lv_label_set_text(bypass_labels[i], tone.enabled[i] ? "ON" : "BYPASS");
        lv_obj_set_style_text_color(bypass_labels[i], color(tone.enabled[i] ? accent : MUTED), 0);
        lv_obj_set_style_bg_color(bypass_buttons[i], color(tone.enabled[i] ? 0x2A3135 : BG), 0);
    }
    dirty_update();
}
static void select_cb(lv_event_t *e)
{
    selected = (int)(intptr_t)lv_event_get_user_data(e); refresh_chain(); build_editor();
}
static void bypass_cb(lv_event_t *e)
{
    int i = (int)(intptr_t)lv_event_get_user_data(e);
    tone.enabled[i] = !tone.enabled[i]; refresh_chain();
    if(i == selected) build_editor();
}
static void format_value(int p, char *buffer, size_t size)
{
    int v = tone.value[selected][p];
    const amp_parameter_t *spec = &amp_blocks[selected].parameters[p];
    if((selected == AMP_CHORUS || selected == AMP_REVERB) && p == 1)
        snprintf(buffer, size, "%d.%d%s", v / 10, v % 10, spec->unit);
    else snprintf(buffer, size, "%d%s", v, spec->unit);
}
static void update_value(int p)
{
    char buffer[32]; format_value(p, buffer, sizeof(buffer));
    lv_label_set_text(values[p], buffer);
    lv_obj_align(values[p], LV_ALIGN_TOP_MID, 0, 136);
    dirty_update();
}
static void arc_cb(lv_event_t *e)
{
    int p = (int)(intptr_t)lv_event_get_user_data(e);
    tone.value[selected][p] = lv_arc_get_value(lv_event_get_target_obj(e)); update_value(p);
}
static void step_cb(lv_event_t *e)
{
    int id = (int)(intptr_t)lv_event_get_user_data(e), p = id / 2;
    const amp_parameter_t *spec = &amp_blocks[selected].parameters[p];
    int v = tone.value[selected][p] + (id % 2 ? spec->step : -spec->step);
    if(v < spec->min) v = spec->min;
    if(v > spec->max) v = spec->max;
    tone.value[selected][p] = v; lv_arc_set_value(arcs[p], v); update_value(p);
}
static void voice_cb(lv_event_t *e)
{
    tone.voice = (int)(intptr_t)lv_event_get_user_data(e); build_editor(); dirty_update();
}
static void build_editor(void)
{
    lv_obj_clean(editor);
    const amp_block_t *block = &amp_blocks[selected];
    unsigned accent = block->color;
    label(editor, selected == AMP_AMP ? "AMPLIFIER" : block->name, 20, 16, accent, &lv_font_montserrat_14);
    if(selected == AMP_AMP) {
        for(int i = 0; i < 3; i++) {
            voice_buttons[i] = button(editor, amp_voices[i], 16, 48 + i * 54, 218, 46,
                                     i == tone.voice ? 0x46392A : 0x252B2F, voice_cb, i);
            if(i == tone.voice) lv_obj_set_style_border_color(voice_buttons[i], color(AMBER), 0);
        }
        label(editor, amp_voice_details[tone.voice], 20, 220, MUTED, &lv_font_montserrat_14);
    } else {
        label(editor, tone.enabled[selected] ? "Effect active" : "Effect bypassed", 20, 51, INK, &lv_font_montserrat_24);
        lv_obj_t *desc = label(editor, block->description, 20, 91, MUTED, &lv_font_montserrat_16);
        lv_obj_set_width(desc, 206);
        button(editor, tone.enabled[selected] ? "Bypass effect" : "Enable effect", 20, 171, 204, 56, 0x2B3236, bypass_cb, selected);
    }
    lv_obj_t *divider = box(editor, 251, 20, 1, 218, EDGE); lv_obj_set_style_radius(divider, 0, 0);
    int width = (732 - 12 * (block->count - 1)) / block->count;
    for(int p = 0; p < block->count; p++) {
        const amp_parameter_t *spec = &block->parameters[p];
        lv_obj_t *card = box(editor, 268 + p * (width + 12), 16, width, 228, PANEL);
        lv_obj_t *name = label(card, spec->name, 0, 0, MUTED, &lv_font_montserrat_16);
        lv_obj_align(name, LV_ALIGN_TOP_MID, 0, 0);
        lv_obj_t *arc = lv_arc_create(card); arcs[p] = arc;
        lv_obj_set_size(arc, 102, 102); lv_obj_align(arc, LV_ALIGN_TOP_MID, 0, 30);
        lv_arc_set_rotation(arc, 135); lv_arc_set_bg_angles(arc, 0, 270);
        lv_arc_set_range(arc, spec->min, spec->max); lv_arc_set_value(arc, tone.value[selected][p]);
        lv_obj_set_style_arc_color(arc, color(EDGE), LV_PART_MAIN);
        lv_obj_set_style_arc_color(arc, color(accent), LV_PART_INDICATOR);
        lv_obj_set_style_arc_width(arc, 7, LV_PART_MAIN); lv_obj_set_style_arc_width(arc, 7, LV_PART_INDICATOR);
        lv_obj_set_style_bg_color(arc, color(INK), LV_PART_KNOB); lv_obj_set_style_pad_all(arc, 3, LV_PART_KNOB);
        lv_obj_add_event_cb(arc, arc_cb, LV_EVENT_VALUE_CHANGED, (void *)(intptr_t)p);
        values[p] = label(card, "", 0, 0, INK, &lv_font_montserrat_24); update_value(p);
        button(card, "-", width / 2 - 57, 172, 52, 52, 0x282F33, step_cb, p * 2);
        button(card, "+", width / 2 + 5, 172, 52, 52, 0x282F33, step_cb, p * 2 + 1);
    }
}
static void close_modal(lv_event_t *e)
{
    (void)e; if(modal) { lv_obj_delete(modal); modal = NULL; }
}
static lv_obj_t *open_modal(const char *title, const char *subtitle)
{
    close_modal(NULL);
    modal = box(root, 0, 0, 1024, 600, BG); lv_obj_set_style_bg_opa(modal, LV_OPA_80, 0);
    lv_obj_set_style_radius(modal, 0, 0); lv_obj_add_flag(modal, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_t *panel = box(modal, 152, 74, 720, 452, PANEL);
    label(panel, title, 28, 26, INK, &lv_font_montserrat_28);
    label(panel, subtitle, 28, 66, MUTED, &lv_font_montserrat_16);
    button(panel, LV_SYMBOL_CLOSE, 632, 20, 60, 52, 0x2B3236, close_modal, 0);
    return panel;
}
static void save_cb(lv_event_t *e)
{
    (void)e; saved[preset] = tone; dirty_update(); toast("Preset saved for this session");
}
static void load_preset(int id)
{
    preset = id; tone = saved[id];
    lv_label_set_text(preset_label, amp_preset_names[preset]); refresh_chain(); build_editor(); close_modal(NULL);
}
static void confirm_load_cb(lv_event_t *e) { load_preset((int)(intptr_t)lv_event_get_user_data(e)); }
static void load_cb(lv_event_t *e)
{
    int id = (int)(intptr_t)lv_event_get_user_data(e);
    if(!amp_tone_equal(&tone, &saved[preset])) {
        lv_obj_t *panel = open_modal("Keep your changes?", "This preset has edits that have not been saved.");
        label(panel, "Close this dialog and Save to keep your tone,\nor discard edits to load the selected preset.", 28, 142, INK, &lv_font_montserrat_24);
        button(panel, "Keep editing", 28, 330, 260, 64, 0x2B3236, close_modal, 0);
        button(panel, "Discard and load", 316, 330, 374, 64, 0x46392A, confirm_load_cb, id);
    } else load_preset(id);
}
static void presets_cb(lv_event_t *e)
{
    (void)e;
    lv_obj_t *panel = open_modal("Your tones", "Three starting points. Make each one your own.");
    for(int i = 0; i < 3; i++) {
        char text[100]; snprintf(text, sizeof(text), "%s       %s", amp_preset_names[i], i == preset ? "CURRENT" : "LOAD");
        load_buttons[i] = button(panel, text, 28, 114 + i * 86, 664, 72, i == preset ? 0x46392A : 0x282F33, load_cb, i);
    }
    label(panel, "Prototype: saved tones reset when the simulator closes.", 28, 400, MUTED, &lv_font_montserrat_14);
}
static void master_cb(lv_event_t *e)
{
    master = lv_slider_get_value(lv_event_get_target_obj(e));
    lv_label_set_text_fmt(volume_label, "%d%%", master);
}
static void mute_cb(lv_event_t *e)
{
    (void)e; muted = !muted;
    lv_label_set_text(lv_obj_get_child(mute_button, 0), muted ? "UNMUTE" : "MUTE");
    lv_obj_set_style_border_color(mute_button, color(muted ? 0xEA8C83 : EDGE), 0);
    toast(muted ? "Output muted (simulation)" : "Output unmuted (simulation)");
}
static void aux_cb(lv_event_t *e)
{
    aux = lv_slider_get_value(lv_event_get_target_obj(e));
    lv_obj_t *value = lv_event_get_user_data(e); lv_label_set_text_fmt(value, "AUX mix   %d%%", aux);
}
static void route_cb(lv_event_t *e)
{
    headphones = !headphones;
    lv_label_set_text(lv_obj_get_child(lv_event_get_target_obj(e), 0), headphones ? "Headphones / speaker off" : "Speaker output");
}
static void settings_cb(lv_event_t *e)
{
    (void)e;
    lv_obj_t *panel = open_modal("Output & device", "SIMULATION  /  No audio hardware connected");
    label(panel, "Output routing", 28, 124, MUTED, &lv_font_montserrat_16);
    button(panel, headphones ? "Headphones / speaker off" : "Speaker output", 28, 152, 664, 60, 0x2B3236, route_cb, 0);
    lv_obj_t *value = label(panel, "", 28, 238, INK, &lv_font_montserrat_16);
    lv_label_set_text_fmt(value, "AUX mix   %d%%", aux);
    lv_obj_t *slider = lv_slider_create(panel); lv_obj_set_pos(slider, 44, 289); lv_obj_set_size(slider, 630, 12);
    lv_slider_set_value(slider, aux, LV_ANIM_OFF); lv_obj_set_ext_click_area(slider, 22);
    lv_obj_set_style_bg_color(slider, color(EDGE), LV_PART_MAIN);
    lv_obj_set_style_bg_color(slider, color(AMBER), LV_PART_INDICATOR);
    lv_obj_set_style_bg_color(slider, color(INK), LV_PART_KNOB);
    lv_obj_add_event_cb(slider, aux_cb, LV_EVENT_VALUE_CHANGED, value);
    label(panel, "Battery telemetry: not connected\nUSB audio and footswitch: future integration", 28, 357, MUTED, &lv_font_montserrat_16);
}
void amp_ui_init(void)
{
    for(int i = 0; i < 3; i++) amp_factory_tone(i, &saved[i]);
    preset = 0; selected = AMP_AMP; tone = saved[0];
    root = lv_screen_active(); lv_obj_remove_style_all(root);
    lv_obj_set_style_bg_color(root, color(BG), 0); lv_obj_set_style_bg_opa(root, LV_OPA_COVER, 0);
    lv_obj_remove_flag(root, LV_OBJ_FLAG_SCROLLABLE);
    preset_label = label(root, amp_preset_names[preset], 24, 25, INK, &lv_font_montserrat_24);
    dirty_label = label(root, "SAVED", 25, 56, MUTED, &lv_font_montserrat_14);
    save_button = button(root, "Save", 660, 20, 98, 56, 0x46392A, save_cb, 0);
    label(root, "UI PROTOTYPE", 804, 26, MUTED, &lv_font_montserrat_14);
    label(root, "BAT --   /   OFFLINE", 804, 50, MUTED, &lv_font_montserrat_14);
    label(root, "SIGNAL CHAIN   /   INPUT TO OUTPUT", 24, 103, MUTED, &lv_font_montserrat_14);
    label(root, "Select to edit  /  Switch to bypass", 704, 103, MUTED, &lv_font_montserrat_14);
    for(int i = 0; i < AMP_BLOCK_COUNT; i++) {
        int x = 24 + i * 140;
        select_buttons[i] = button(root, amp_blocks[i].name, x, 132, 136, 60, PANEL, select_cb, i);
        lv_obj_set_style_text_color(lv_obj_get_child(select_buttons[i], 0), color(amp_blocks[i].color), 0);
        bypass_buttons[i] = button(root, "", x, 196, 136, 44, BG, bypass_cb, i);
        bypass_labels[i] = lv_obj_get_child(bypass_buttons[i], 0);
    }
    editor = box(root, 8, 256, 1008, 260, PANEL); build_editor();
    button(root, "Presets", 24, 534, 142, 54, 0x282F33, presets_cb, 0);
    button(root, "Settings", 178, 534, 142, 54, 0x282F33, settings_cb, 0);
    label(root, "MASTER", 372, 552, MUTED, &lv_font_montserrat_14);
    master_slider = lv_slider_create(root); lv_obj_set_pos(master_slider, 470, 556); lv_obj_set_size(master_slider, 290, 10);
    lv_slider_set_value(master_slider, master, LV_ANIM_OFF); lv_obj_set_ext_click_area(master_slider, 22);
    lv_obj_set_style_bg_color(master_slider, color(EDGE), LV_PART_MAIN);
    lv_obj_set_style_bg_color(master_slider, color(AMBER), LV_PART_INDICATOR);
    lv_obj_set_style_bg_color(master_slider, color(INK), LV_PART_KNOB);
    lv_obj_add_event_cb(master_slider, master_cb, LV_EVENT_VALUE_CHANGED, NULL);
    volume_label = label(root, "65%", 792, 550, INK, &lv_font_montserrat_24);
    mute_button = button(root, "MUTE", 880, 534, 120, 54, 0x282F33, mute_cb, 0);
    toast_label = label(root, "", 372, 520, AMBER, &lv_font_montserrat_14);
    toast_timer = lv_timer_create(toast_clear, 2800, NULL); lv_timer_pause(toast_timer);
    refresh_chain();
}

/* Exercise actual LVGL events, including transitions that rebuild child objects. */
int amp_ui_smoke_test(void)
{
    int failures = 0;
#define CHECK(x) do { if(!(x)) { fprintf(stderr, "FAIL: %s\n", #x); failures++; } } while(0)
    CHECK(tone.voice == 0 && tone.enabled[AMP_REVERB]);
    lv_obj_send_event(select_buttons[AMP_DELAY], LV_EVENT_CLICKED, NULL);
    CHECK(selected == AMP_DELAY);
    lv_arc_set_value(arcs[1], 620); lv_obj_send_event(arcs[1], LV_EVENT_VALUE_CHANGED, NULL);
    CHECK(tone.value[AMP_DELAY][1] == 620);
    lv_obj_send_event(bypass_buttons[AMP_DELAY], LV_EVENT_CLICKED, NULL);
    CHECK(tone.enabled[AMP_DELAY]);
    CHECK(!amp_tone_equal(&tone, &saved[0]));
    lv_obj_send_event(save_button, LV_EVENT_CLICKED, NULL);
    CHECK(amp_tone_equal(&tone, &saved[0]));
    presets_cb(NULL); lv_obj_send_event(load_buttons[1], LV_EVENT_CLICKED, NULL);
    CHECK(preset == 1 && tone.voice == 1);
    load_preset(0); CHECK(tone.value[AMP_DELAY][1] == 620 && tone.enabled[AMP_DELAY]);
    lv_obj_send_event(select_buttons[AMP_AMP], LV_EVENT_CLICKED, NULL);
    lv_obj_send_event(voice_buttons[2], LV_EVENT_CLICKED, NULL); CHECK(tone.voice == 2);
    presets_cb(NULL); lv_obj_send_event(load_buttons[1], LV_EVENT_CLICKED, NULL);
    CHECK(modal != NULL && preset == 0); close_modal(NULL);
    lv_slider_set_value(master_slider, 42, LV_ANIM_OFF); lv_obj_send_event(master_slider, LV_EVENT_VALUE_CHANGED, NULL);
    CHECK(master == 42);
    lv_obj_send_event(mute_button, LV_EVENT_CLICKED, NULL); CHECK(muted);
    lv_obj_send_event(mute_button, LV_EVENT_CLICKED, NULL); CHECK(!muted);
    for(int i = 0; i < AMP_BLOCK_COUNT; i++) {
        lv_obj_send_event(select_buttons[i], LV_EVENT_CLICKED, NULL);
        for(int p = 0; p < amp_blocks[i].count; p++) {
            lv_arc_set_value(arcs[p], amp_blocks[i].parameters[p].max);
            lv_obj_send_event(arcs[p], LV_EVENT_VALUE_CHANGED, NULL);
            CHECK(tone.value[i][p] == amp_blocks[i].parameters[p].max);
        }
    }
    for(int i = 0; i < 3; i++) amp_factory_tone(i, &saved[i]);
    selected = AMP_AMP; load_preset(0);
    lv_slider_set_value(master_slider, 65, LV_ANIM_OFF); lv_obj_send_event(master_slider, LV_EVENT_VALUE_CHANGED, NULL);
    toast_clear(NULL);
    fprintf(stdout, "UI smoke checks: %s\n", failures ? "FAILED" : "PASSED");
    return failures;
#undef CHECK
}

/* Stable scenes for visual QA: amp, delay, presets, settings, dirty warning. */
void amp_ui_preview_scene(int scene)
{
    if(scene == 1) lv_obj_send_event(select_buttons[AMP_DELAY], LV_EVENT_CLICKED, NULL);
    if(scene == 2) presets_cb(NULL);
    if(scene == 3) settings_cb(NULL);
    if(scene == 4) {
        tone.value[AMP_AMP][0] = 60; dirty_update();
        presets_cb(NULL); lv_obj_send_event(load_buttons[1], LV_EVENT_CLICKED, NULL);
    }
}
