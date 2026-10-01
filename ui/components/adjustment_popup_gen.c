/**
 * @file adjustment_popup_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "adjustment_popup_gen.h"
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

lv_obj_t * adjustment_popup_create(lv_obj_t * parent, int32_t control_id, const char * title, lv_subject_t * subject, const char * format, int32_t minimum, int32_t maximum, lv_color_t accent)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if AMP_EDITOR_CHECK_COMPILE_TARGET(AMP_EDITOR_TARGET_ALL)
    if (amp_editor_check_target(AMP_EDITOR_TARGET_ALL)) {
        lv_obj_t * lv_obj_0 = lv_obj_create(parent);
        lv_obj_set_name_static(lv_obj_0, "adjustment_popup_#");
        lv_obj_set_style_bg_opa(lv_obj_0, (255 * 0 / 100), 0);
        lv_obj_set_style_border_width(lv_obj_0, 0, 0);
        lv_obj_set_style_pad_all(lv_obj_0, 0, 0);
        lv_obj_set_style_radius(lv_obj_0, 0, 0);
        lv_obj_set_flag(lv_obj_0, LV_OBJ_FLAG_SCROLLABLE, false);
        lv_obj_set_width(lv_obj_0, 1024);
        lv_obj_set_height(lv_obj_0, 600);
        lv_obj_set_flag(lv_obj_0, LV_OBJ_FLAG_CLICKABLE, false);

        lv_obj_bind_flag_if_not_eq(lv_obj_0, &active_adjustment, LV_OBJ_FLAG_HIDDEN, control_id);
        lv_obj_t * lv_obj_1 = lv_obj_create(lv_obj_0);
        lv_obj_set_style_bg_opa(lv_obj_1, LV_OPA_TRANSP, 0);
        lv_obj_set_style_border_width(lv_obj_1, 0, 0);
        lv_obj_set_style_pad_all(lv_obj_1, 0, 0);
        lv_obj_set_style_radius(lv_obj_1, 0, 0);
        lv_obj_set_flag(lv_obj_1, LV_OBJ_FLAG_SCROLLABLE, false);
        lv_obj_set_width(lv_obj_1, 1024);
        lv_obj_set_height(lv_obj_1, 600);
        lv_obj_set_flag(lv_obj_1, LV_OBJ_FLAG_CLICKABLE, true);
        lv_obj_set_flag(lv_obj_1, LV_OBJ_FLAG_GESTURE_BUBBLE, false);
        lv_obj_set_style_bg_color(lv_obj_1, BACKGROUND, 0);
        lv_obj_add_subject_set_int_event(lv_obj_1, &active_adjustment, LV_EVENT_CLICKED, 0);

        lv_obj_t * value_panel = lv_obj_create(lv_obj_0);
        lv_obj_set_name(value_panel, "value_panel");
        lv_obj_set_x(value_panel, 704);
        lv_obj_set_y(value_panel, 84);
        lv_obj_set_width(value_panel, 304);
        lv_obj_set_height(value_panel, 448);
        lv_obj_set_flag(value_panel, LV_OBJ_FLAG_SCROLLABLE, false);
        lv_obj_set_flag(value_panel, LV_OBJ_FLAG_CLICKABLE, true);
        lv_obj_set_flag(value_panel, LV_OBJ_FLAG_GESTURE_BUBBLE, false);
        lv_obj_set_style_bg_color(value_panel, lv_color_hex(0x20292F), 0);
        lv_obj_set_style_bg_opa(value_panel, (255 * 88 / 100), 0);
        lv_obj_set_style_border_width(value_panel, 1, 0);
        lv_obj_set_style_border_color(value_panel, EDGE, 0);
        lv_obj_set_style_pad_all(value_panel, 0, 0);
        lv_obj_set_style_radius(value_panel, 24, 0);
        lv_obj_set_style_shadow_width(value_panel, 0, 0);
        lv_obj_set_style_shadow_opa(value_panel, (255 * 20 / 100), 0);
        lv_obj_t * lv_label_0 = lv_label_create(value_panel);
        lv_label_set_text(lv_label_0, title);
        lv_obj_set_x(lv_label_0, 24);
        lv_obj_set_y(lv_label_0, 22);
        lv_obj_set_width(lv_label_0, 218);
        lv_obj_set_style_text_font(lv_label_0, font_20, 0);
        lv_obj_set_style_text_color(lv_label_0, accent, 0);

        lv_obj_t * amp_button_0 = amp_button_create(value_panel, "X");
        lv_obj_set_x(amp_button_0, 244);
        lv_obj_set_y(amp_button_0, 12);
        lv_obj_set_width(amp_button_0, 48);
        lv_obj_set_height(amp_button_0, 48);
        lv_obj_set_style_bg_opa(amp_button_0, (255 * 0 / 100), 0);
        lv_obj_set_style_border_width(amp_button_0, 0, 0);
        lv_obj_add_subject_set_int_event(amp_button_0, &active_adjustment, LV_EVENT_CLICKED, 0);

        lv_obj_t * lv_label_1 = lv_label_create(value_panel);
        lv_obj_set_align(lv_label_1, LV_ALIGN_TOP_MID);
        lv_obj_set_y(lv_label_1, 70);
        lv_obj_set_name(lv_label_1, "value_readout");
        lv_obj_set_size(lv_label_1, 256, 64);
        lv_obj_set_style_text_align(lv_label_1, LV_TEXT_ALIGN_CENTER, 0);
        lv_obj_set_style_bg_color(lv_label_1, lv_color_hex(0x20292F), 0);
        lv_obj_set_style_bg_opa(lv_label_1, LV_OPA_COVER, 0);
        lv_label_bind_text(lv_label_1, subject, format);
        lv_obj_set_style_text_font(lv_label_1, font_48, 0);
        lv_obj_set_style_text_color(lv_label_1, INK, 0);

        lv_obj_t * swipe_control = lv_slider_create(value_panel);
        lv_obj_set_name(swipe_control, "swipe_control");
        lv_obj_set_x(swipe_control, 116);
        lv_obj_set_y(swipe_control, 152);
        lv_obj_set_width(swipe_control, 72);
        lv_obj_set_height(swipe_control, 222);
        lv_slider_set_min_value(swipe_control, minimum);
        lv_slider_set_max_value(swipe_control, maximum);
        lv_slider_bind_value(swipe_control, subject);
        lv_slider_set_orientation(swipe_control, LV_SLIDER_ORIENTATION_VERTICAL);
        lv_obj_set_ext_click_area(swipe_control, 78);
        lv_obj_set_flag(swipe_control, LV_OBJ_FLAG_GESTURE_BUBBLE, false);
        lv_obj_set_style_radius(swipe_control, 18, 0);
        lv_obj_set_style_bg_color(swipe_control, EDGE, 0);
        lv_obj_set_style_bg_opa(swipe_control, LV_OPA_COVER, 0);
        lv_obj_set_style_bg_color(swipe_control, accent, LV_PART_INDICATOR);
        lv_obj_set_style_bg_opa(swipe_control, LV_OPA_COVER, LV_PART_INDICATOR);
        lv_obj_set_style_radius(swipe_control, 18, LV_PART_INDICATOR);
        lv_obj_set_style_bg_color(swipe_control, INK, LV_PART_KNOB);
        lv_obj_set_style_bg_opa(swipe_control, (255 * 100 / 100), LV_PART_KNOB);
        lv_obj_set_style_pad_top(swipe_control, -31, LV_PART_KNOB);
        lv_obj_set_style_pad_bottom(swipe_control, -31, LV_PART_KNOB);
        lv_obj_set_style_pad_left(swipe_control, 6, LV_PART_KNOB);
        lv_obj_set_style_pad_right(swipe_control, 6, LV_PART_KNOB);
        lv_obj_set_style_radius(swipe_control, 5, LV_PART_KNOB);
        lv_obj_add_subject_set_int_event(swipe_control, &edited, LV_EVENT_VALUE_CHANGED, 1);

        lv_obj_t * lv_label_2 = lv_label_create(value_panel);
        lv_label_set_text(lv_label_2, "Swipe up to raise\nSwipe down to lower");
        lv_obj_set_align(lv_label_2, LV_ALIGN_BOTTOM_MID);
        lv_obj_set_y(lv_label_2, -20);
        lv_obj_set_style_text_align(lv_label_2, LV_TEXT_ALIGN_CENTER, 0);
        lv_obj_set_style_text_font(lv_label_2, font_14, 0);
        lv_obj_set_style_text_color(lv_label_2, MUTED, 0);

        the_root = lv_obj_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

