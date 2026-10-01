/**
 * @file preview_dialogs_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "preview_dialogs_gen.h"
#include "../amp_editor.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/***********************
 *  STATIC VARIABLES
 **********************/

/***********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t * preview_dialogs_create(lv_obj_t * parent)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if AMP_EDITOR_CHECK_COMPILE_TARGET(AMP_EDITOR_TARGET_ALL)
    if (amp_editor_check_target(AMP_EDITOR_TARGET_ALL)) {
        lv_obj_t * lv_obj_0 = lv_obj_create(parent);
        lv_obj_set_name_static(lv_obj_0, "preview_dialogs_#");
        lv_obj_set_width(lv_obj_0, 1024);
        lv_obj_set_height(lv_obj_0, 600);
        lv_obj_set_flag(lv_obj_0, LV_OBJ_FLAG_SCROLLABLE, false);
        lv_obj_set_flag(lv_obj_0, LV_OBJ_FLAG_CLICKABLE, false);
        lv_obj_set_style_bg_color(lv_obj_0, BACKGROUND, 0);
        lv_obj_set_style_bg_opa(lv_obj_0, (255 * 80 / 100), 0);
        lv_obj_set_style_pad_all(lv_obj_0, 0, 0);
        lv_obj_set_style_border_width(lv_obj_0, 0, 0);
        lv_obj_set_style_radius(lv_obj_0, 0, 0);

        lv_obj_bind_flag_if_eq(lv_obj_0, &dialog, LV_OBJ_FLAG_HIDDEN, 0);
        lv_obj_t * dismiss_area = lv_obj_create(lv_obj_0);
        lv_obj_set_name(dismiss_area, "dismiss_area");
        lv_obj_set_width(dismiss_area, 1024);
        lv_obj_set_height(dismiss_area, 600);
        lv_obj_set_flag(dismiss_area, LV_OBJ_FLAG_SCROLLABLE, false);
        lv_obj_set_flag(dismiss_area, LV_OBJ_FLAG_CLICKABLE, true);
        lv_obj_set_flag(dismiss_area, LV_OBJ_FLAG_GESTURE_BUBBLE, false);
        lv_obj_set_style_bg_opa(dismiss_area, (255 * 0 / 100), 0);
        lv_obj_set_style_border_width(dismiss_area, 0, 0);
        lv_obj_set_style_pad_all(dismiss_area, 0, 0);
        lv_obj_set_style_radius(dismiss_area, 0, 0);
        lv_obj_add_subject_set_int_event(dismiss_area, &dialog, LV_EVENT_CLICKED, 0);

        lv_obj_t * lv_obj_1 = lv_obj_create(lv_obj_0);
        lv_obj_set_x(lv_obj_1, 152);
        lv_obj_set_y(lv_obj_1, 74);
        lv_obj_set_width(lv_obj_1, 720);
        lv_obj_set_height(lv_obj_1, 452);
        lv_obj_set_flag(lv_obj_1, LV_OBJ_FLAG_SCROLLABLE, false);
        lv_obj_set_flag(lv_obj_1, LV_OBJ_FLAG_CLICKABLE, true);
        lv_obj_set_flag(lv_obj_1, LV_OBJ_FLAG_GESTURE_BUBBLE, false);
        lv_obj_add_style(lv_obj_1, &surface, 0);
        lv_obj_t * amp_button_0 = amp_button_create(lv_obj_1, "X");
        lv_obj_set_x(amp_button_0, 632);
        lv_obj_set_y(amp_button_0, 20);
        lv_obj_set_width(amp_button_0, 60);
        lv_obj_set_height(amp_button_0, 52);
        lv_obj_add_subject_set_int_event(amp_button_0, &dialog, LV_EVENT_CLICKED, 0);

        lv_obj_t * lv_label_0 = lv_label_create(lv_obj_1);
        lv_label_set_text(lv_label_0, "Your tones");
        lv_obj_set_x(lv_label_0, 28);
        lv_obj_set_y(lv_label_0, 26);
        lv_obj_set_style_text_font(lv_label_0, font_28, 0);
        lv_obj_set_style_text_color(lv_label_0, INK, 0);
        lv_obj_bind_flag_if_not_eq(lv_label_0, &dialog, LV_OBJ_FLAG_HIDDEN, 1);

        lv_obj_t * lv_label_1 = lv_label_create(lv_obj_1);
        lv_label_set_text(lv_label_1, "Choose a preset label for your preview.");
        lv_obj_set_x(lv_label_1, 28);
        lv_obj_set_y(lv_label_1, 66);
        lv_obj_set_style_text_font(lv_label_1, font_16, 0);
        lv_obj_set_style_text_color(lv_label_1, MUTED, 0);
        lv_obj_bind_flag_if_not_eq(lv_label_1, &dialog, LV_OBJ_FLAG_HIDDEN, 1);

        lv_obj_t * lv_obj_2 = lv_obj_create(lv_obj_1);
        lv_obj_set_x(lv_obj_2, 0);
        lv_obj_set_y(lv_obj_2, 108);
        lv_obj_set_width(lv_obj_2, 720);
        lv_obj_set_height(lv_obj_2, 336);
        lv_obj_set_flag(lv_obj_2, LV_OBJ_FLAG_SCROLLABLE, false);
        lv_obj_set_style_bg_opa(lv_obj_2, (255 * 0 / 100), 0);
        lv_obj_set_style_border_width(lv_obj_2, 0, 0);
        lv_obj_set_style_pad_all(lv_obj_2, 0, 0);
        lv_obj_set_style_radius(lv_obj_2, 0, 0);
        lv_obj_set_style_shadow_width(lv_obj_2, 0, 0);
        lv_obj_bind_flag_if_not_eq(lv_obj_2, &dialog, LV_OBJ_FLAG_HIDDEN, 1);
        lv_obj_t * amp_button_1 = amp_button_create(lv_obj_2, "Preset 1");
        lv_obj_set_x(amp_button_1, 28);
        lv_obj_set_y(amp_button_1, 6);
        lv_obj_set_width(amp_button_1, 664);
        lv_obj_set_height(amp_button_1, 72);
        lv_obj_set_style_bg_color(amp_button_1, SELECTED_BG, LV_STATE_CHECKED);
        lv_obj_bind_state_if_eq(amp_button_1, &preset_number, LV_STATE_CHECKED, 1);
        lv_obj_add_subject_set_int_event(amp_button_1, &preset_number, LV_EVENT_CLICKED, 1);
        lv_obj_add_subject_set_int_event(amp_button_1, &dialog, LV_EVENT_CLICKED, 0);

        lv_obj_t * amp_button_2 = amp_button_create(lv_obj_2, "Preset 2");
        lv_obj_set_x(amp_button_2, 28);
        lv_obj_set_y(amp_button_2, 92);
        lv_obj_set_width(amp_button_2, 664);
        lv_obj_set_height(amp_button_2, 72);
        lv_obj_set_style_bg_color(amp_button_2, SELECTED_BG, LV_STATE_CHECKED);
        lv_obj_bind_state_if_eq(amp_button_2, &preset_number, LV_STATE_CHECKED, 2);
        lv_obj_add_subject_set_int_event(amp_button_2, &preset_number, LV_EVENT_CLICKED, 2);
        lv_obj_add_subject_set_int_event(amp_button_2, &dialog, LV_EVENT_CLICKED, 0);

        lv_obj_t * amp_button_3 = amp_button_create(lv_obj_2, "Preset 3");
        lv_obj_set_x(amp_button_3, 28);
        lv_obj_set_y(amp_button_3, 178);
        lv_obj_set_width(amp_button_3, 664);
        lv_obj_set_height(amp_button_3, 72);
        lv_obj_set_style_bg_color(amp_button_3, SELECTED_BG, LV_STATE_CHECKED);
        lv_obj_bind_state_if_eq(amp_button_3, &preset_number, LV_STATE_CHECKED, 3);
        lv_obj_add_subject_set_int_event(amp_button_3, &preset_number, LV_EVENT_CLICKED, 3);
        lv_obj_add_subject_set_int_event(amp_button_3, &dialog, LV_EVENT_CLICKED, 0);

        lv_obj_t * lv_label_2 = lv_label_create(lv_obj_2);
        lv_label_set_text(lv_label_2, "Preview labels only; preset save/recall remains in the C simulator.");
        lv_obj_set_x(lv_label_2, 28);
        lv_obj_set_y(lv_label_2, 292);
        lv_obj_set_style_text_font(lv_label_2, font_14, 0);
        lv_obj_set_style_text_color(lv_label_2, MUTED, 0);

        lv_obj_t * lv_label_3 = lv_label_create(lv_obj_1);
        lv_label_set_text(lv_label_3, "Output & device");
        lv_obj_set_x(lv_label_3, 28);
        lv_obj_set_y(lv_label_3, 26);
        lv_obj_set_style_text_font(lv_label_3, font_28, 0);
        lv_obj_set_style_text_color(lv_label_3, INK, 0);
        lv_obj_bind_flag_if_not_eq(lv_label_3, &dialog, LV_OBJ_FLAG_HIDDEN, 2);

        lv_obj_t * lv_label_4 = lv_label_create(lv_obj_1);
        lv_label_set_text(lv_label_4, "SIMULATION / No audio hardware connected");
        lv_obj_set_x(lv_label_4, 28);
        lv_obj_set_y(lv_label_4, 66);
        lv_obj_set_style_text_font(lv_label_4, font_16, 0);
        lv_obj_set_style_text_color(lv_label_4, MUTED, 0);
        lv_obj_bind_flag_if_not_eq(lv_label_4, &dialog, LV_OBJ_FLAG_HIDDEN, 2);

        lv_obj_t * lv_obj_3 = lv_obj_create(lv_obj_1);
        lv_obj_set_x(lv_obj_3, 0);
        lv_obj_set_y(lv_obj_3, 108);
        lv_obj_set_width(lv_obj_3, 720);
        lv_obj_set_height(lv_obj_3, 336);
        lv_obj_set_flag(lv_obj_3, LV_OBJ_FLAG_SCROLLABLE, false);
        lv_obj_set_style_bg_opa(lv_obj_3, (255 * 0 / 100), 0);
        lv_obj_set_style_border_width(lv_obj_3, 0, 0);
        lv_obj_set_style_pad_all(lv_obj_3, 0, 0);
        lv_obj_set_style_radius(lv_obj_3, 0, 0);
        lv_obj_set_style_shadow_width(lv_obj_3, 0, 0);
        lv_obj_bind_flag_if_not_eq(lv_obj_3, &dialog, LV_OBJ_FLAG_HIDDEN, 2);
        lv_obj_t * lv_label_5 = lv_label_create(lv_obj_3);
        lv_label_set_text(lv_label_5, "Output routing");
        lv_obj_set_x(lv_label_5, 28);
        lv_obj_set_y(lv_label_5, 16);
        lv_obj_set_style_text_font(lv_label_5, font_16, 0);
        lv_obj_set_style_text_color(lv_label_5, MUTED, 0);

        lv_obj_t * amp_button_4 = amp_button_create(lv_obj_3, "");
        lv_obj_set_x(amp_button_4, 28);
        lv_obj_set_y(amp_button_4, 44);
        lv_obj_set_width(amp_button_4, 664);
        lv_obj_set_height(amp_button_4, 60);
        lv_obj_add_subject_toggle_event(amp_button_4, &headphones, LV_EVENT_CLICKED);
        lv_obj_t * lv_label_6 = lv_label_create(amp_button_4);
        lv_label_set_text(lv_label_6, "Speaker output");
        lv_obj_set_x(lv_label_6, 0);
        lv_obj_set_y(lv_label_6, 0);
        lv_obj_set_style_text_font(lv_label_6, font_16, 0);
        lv_obj_set_style_text_color(lv_label_6, INK, 0);
        lv_obj_set_align(lv_label_6, LV_ALIGN_CENTER);
        lv_obj_bind_flag_if_not_eq(lv_label_6, &headphones, LV_OBJ_FLAG_HIDDEN, 0);

        lv_obj_t * lv_label_7 = lv_label_create(amp_button_4);
        lv_label_set_text(lv_label_7, "Headphones / speaker off");
        lv_obj_set_x(lv_label_7, 0);
        lv_obj_set_y(lv_label_7, 0);
        lv_obj_set_style_text_font(lv_label_7, font_16, 0);
        lv_obj_set_style_text_color(lv_label_7, INK, 0);
        lv_obj_set_align(lv_label_7, LV_ALIGN_CENTER);
        lv_obj_bind_flag_if_not_eq(lv_label_7, &headphones, LV_OBJ_FLAG_HIDDEN, 1);

        lv_obj_t * lv_label_8 = lv_label_create(lv_obj_3);
        lv_obj_set_x(lv_label_8, 28);
        lv_obj_set_y(lv_label_8, 130);
        lv_label_bind_text(lv_label_8, &aux, "AUX mix   %d%%");
        lv_obj_set_style_text_font(lv_label_8, font_16, 0);
        lv_obj_set_style_text_color(lv_label_8, INK, 0);

        lv_obj_t * lv_slider_0 = lv_slider_create(lv_obj_3);
        lv_obj_set_x(lv_slider_0, 44);
        lv_obj_set_y(lv_slider_0, 181);
        lv_obj_set_width(lv_slider_0, 630);
        lv_obj_set_height(lv_slider_0, 12);
        lv_slider_set_min_value(lv_slider_0, 0);
        lv_slider_set_max_value(lv_slider_0, 100);
        lv_slider_bind_value(lv_slider_0, &aux);
        lv_obj_set_ext_click_area(lv_slider_0, 22);
        lv_obj_set_style_bg_color(lv_slider_0, EDGE, 0);
        lv_obj_set_style_bg_color(lv_slider_0, AMBER, LV_PART_INDICATOR);
        lv_obj_set_style_bg_color(lv_slider_0, INK, LV_PART_KNOB);
        lv_obj_add_subject_set_int_event(lv_slider_0, &edited, LV_EVENT_VALUE_CHANGED, 1);

        lv_obj_t * lv_label_9 = lv_label_create(lv_obj_3);
        lv_label_set_text(lv_label_9, "Battery telemetry: not connected\nUSB audio and footswitch: future integration");
        lv_obj_set_x(lv_label_9, 28);
        lv_obj_set_y(lv_label_9, 249);
        lv_obj_set_style_text_font(lv_label_9, font_16, 0);
        lv_obj_set_style_text_color(lv_label_9, MUTED, 0);

        lv_obj_t * open_aux = lv_obj_create(lv_obj_3);
        lv_obj_set_style_bg_opa(open_aux, (255 * 0 / 100), 0);
        lv_obj_set_style_border_width(open_aux, 0, 0);
        lv_obj_set_style_pad_all(open_aux, 0, 0);
        lv_obj_set_style_radius(open_aux, 0, 0);
        lv_obj_set_flag(open_aux, LV_OBJ_FLAG_SCROLLABLE, false);
        lv_obj_set_name(open_aux, "open_aux");
        lv_obj_set_x(open_aux, 22);
        lv_obj_set_y(open_aux, 122);
        lv_obj_set_width(open_aux, 252);
        lv_obj_set_height(open_aux, 34);
        lv_obj_set_flag(open_aux, LV_OBJ_FLAG_CLICKABLE, true);
        lv_obj_add_subject_set_int_event(open_aux, &active_adjustment, LV_EVENT_SHORT_CLICKED, 101);

        lv_obj_t * lv_label_10 = lv_label_create(lv_obj_1);
        lv_label_set_text(lv_label_10, "Preview only");
        lv_obj_set_x(lv_label_10, 28);
        lv_obj_set_y(lv_label_10, 26);
        lv_obj_set_style_text_font(lv_label_10, font_28, 0);
        lv_obj_set_style_text_color(lv_label_10, INK, 0);
        lv_obj_bind_flag_if_not_eq(lv_label_10, &dialog, LV_OBJ_FLAG_HIDDEN, 3);

        lv_obj_t * lv_label_11 = lv_label_create(lv_obj_1);
        lv_label_set_text(lv_label_11, "Layout edits are saved by the LVGL Pro editor.");
        lv_obj_set_x(lv_label_11, 28);
        lv_obj_set_y(lv_label_11, 66);
        lv_obj_set_style_text_font(lv_label_11, font_16, 0);
        lv_obj_set_style_text_color(lv_label_11, MUTED, 0);
        lv_obj_bind_flag_if_not_eq(lv_label_11, &dialog, LV_OBJ_FLAG_HIDDEN, 3);

        lv_obj_t * lv_obj_4 = lv_obj_create(lv_obj_1);
        lv_obj_set_x(lv_obj_4, 0);
        lv_obj_set_y(lv_obj_4, 108);
        lv_obj_set_width(lv_obj_4, 720);
        lv_obj_set_height(lv_obj_4, 336);
        lv_obj_set_flag(lv_obj_4, LV_OBJ_FLAG_SCROLLABLE, false);
        lv_obj_set_style_bg_opa(lv_obj_4, (255 * 0 / 100), 0);
        lv_obj_set_style_border_width(lv_obj_4, 0, 0);
        lv_obj_set_style_pad_all(lv_obj_4, 0, 0);
        lv_obj_set_style_radius(lv_obj_4, 0, 0);
        lv_obj_set_style_shadow_width(lv_obj_4, 0, 0);
        lv_obj_bind_flag_if_not_eq(lv_obj_4, &dialog, LV_OBJ_FLAG_HIDDEN, 3);
        lv_obj_t * lv_label_12 = lv_label_create(lv_obj_4);
        lv_label_set_text(lv_label_12, "Dials and switches work in this preview.\nSaving audio presets is handled by the\noriginal C simulator, not this layout preview.");
        lv_obj_set_x(lv_label_12, 28);
        lv_obj_set_y(lv_label_12, 34);
        lv_obj_set_style_text_font(lv_label_12, font_24, 0);
        lv_obj_set_style_text_color(lv_label_12, INK, 0);
        lv_obj_set_width(lv_label_12, 664);

        lv_obj_t * amp_button_5 = amp_button_create(lv_obj_4, "Back to editor preview");
        lv_obj_set_x(amp_button_5, 28);
        lv_obj_set_y(amp_button_5, 222);
        lv_obj_set_width(amp_button_5, 664);
        lv_obj_set_height(amp_button_5, 64);
        lv_obj_add_subject_set_int_event(amp_button_5, &dialog, LV_EVENT_CLICKED, 0);

        the_root = lv_obj_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

