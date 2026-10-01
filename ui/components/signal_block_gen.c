/**
 * @file signal_block_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "signal_block_gen.h"
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

lv_obj_t * signal_block_create(lv_obj_t * parent, const char * title, int32_t block_id, lv_subject_t * enabled_subject, lv_color_t accent)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if AMP_EDITOR_CHECK_COMPILE_TARGET(AMP_EDITOR_TARGET_ALL)
    if (amp_editor_check_target(AMP_EDITOR_TARGET_ALL)) {
        lv_obj_t * lv_obj_0 = lv_obj_create(parent);
        lv_obj_set_name_static(lv_obj_0, "signal_block_#");
        lv_obj_set_width(lv_obj_0, 113);
        lv_obj_set_height(lv_obj_0, 128);
        lv_obj_set_flag(lv_obj_0, LV_OBJ_FLAG_SCROLLABLE, false);
        lv_obj_set_style_bg_opa(lv_obj_0, (255 * 0 / 100), 0);
        lv_obj_set_style_border_width(lv_obj_0, 0, 0);
        lv_obj_set_style_pad_all(lv_obj_0, 0, 0);
        lv_obj_set_style_radius(lv_obj_0, 0, 0);
        lv_obj_set_style_shadow_width(lv_obj_0, 0, 0);

        lv_obj_t * amp_button_0 = amp_button_create(lv_obj_0, title);
        lv_obj_set_x(amp_button_0, 0);
        lv_obj_set_y(amp_button_0, 0);
        lv_obj_set_width(amp_button_0, 113);
        lv_obj_set_height(amp_button_0, 68);
        lv_obj_set_flag(amp_button_0, LV_OBJ_FLAG_PRESS_LOCK, true);
        lv_obj_set_flag(amp_button_0, LV_OBJ_FLAG_GESTURE_BUBBLE, false);
        lv_obj_set_style_bg_color(amp_button_0, PANEL, 0);
        lv_obj_set_style_text_font(amp_button_0, font_16, 0);
        lv_obj_set_style_text_color(amp_button_0, accent, 0);
        lv_obj_set_style_bg_color(amp_button_0, PANEL, LV_STATE_CHECKED);
        lv_obj_set_style_text_color(amp_button_0, accent, LV_STATE_CHECKED);
        lv_obj_set_style_border_color(amp_button_0, accent, LV_STATE_CHECKED);
        lv_obj_set_style_border_width(amp_button_0, 2, LV_STATE_CHECKED);
        lv_obj_bind_state_if_eq(amp_button_0, &selected_block, LV_STATE_CHECKED, block_id);
        lv_obj_add_subject_set_int_event(amp_button_0, &selected_block, LV_EVENT_CLICKED, block_id);
        lv_obj_add_event_cb(amp_button_0, amp_chain_drag_event, LV_EVENT_ALL, NULL);

        lv_obj_t * amp_button_1 = amp_button_create(lv_obj_0, "");
        lv_obj_set_x(amp_button_1, 0);
        lv_obj_set_y(amp_button_1, 74);
        lv_obj_set_width(amp_button_1, 113);
        lv_obj_set_height(amp_button_1, 54);
        lv_obj_set_style_bg_color(amp_button_1, BACKGROUND, 0);
        lv_obj_set_style_bg_color(amp_button_1, lv_color_hex(0x2A3135), LV_STATE_CHECKED);
        lv_obj_bind_state_if_eq(amp_button_1, enabled_subject, LV_STATE_CHECKED, 1);
        lv_obj_add_subject_toggle_event(amp_button_1, enabled_subject, LV_EVENT_CLICKED);
        lv_obj_add_subject_set_int_event(amp_button_1, &edited, LV_EVENT_CLICKED, 1);
        lv_obj_t * lv_label_0 = lv_label_create(amp_button_1);
        lv_label_set_text(lv_label_0, "ON");
        lv_obj_set_x(lv_label_0, 0);
        lv_obj_set_y(lv_label_0, 0);
        lv_obj_set_style_text_font(lv_label_0, font_16, 0);
        lv_obj_set_style_text_color(lv_label_0, accent, 0);
        lv_obj_set_align(lv_label_0, LV_ALIGN_CENTER);
        lv_obj_bind_flag_if_not_eq(lv_label_0, enabled_subject, LV_OBJ_FLAG_HIDDEN, 1);

        lv_obj_t * lv_label_1 = lv_label_create(amp_button_1);
        lv_label_set_text(lv_label_1, "BYPASS");
        lv_obj_set_x(lv_label_1, 0);
        lv_obj_set_y(lv_label_1, 0);
        lv_obj_set_style_text_font(lv_label_1, font_16, 0);
        lv_obj_set_style_text_color(lv_label_1, MUTED, 0);
        lv_obj_set_align(lv_label_1, LV_ALIGN_CENTER);
        lv_obj_bind_flag_if_not_eq(lv_label_1, enabled_subject, LV_OBJ_FLAG_HIDDEN, 0);

        the_root = lv_obj_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

