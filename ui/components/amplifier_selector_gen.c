/**
 * @file amplifier_selector_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "amplifier_selector_gen.h"
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

lv_obj_t * amplifier_selector_create(lv_obj_t * parent)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if AMP_EDITOR_CHECK_COMPILE_TARGET(AMP_EDITOR_TARGET_ALL)
    if (amp_editor_check_target(AMP_EDITOR_TARGET_ALL)) {
        lv_obj_t * lv_obj_0 = lv_obj_create(parent);
        lv_obj_set_name_static(lv_obj_0, "amplifier_selector_#");
        lv_obj_set_width(lv_obj_0, 420);
        lv_obj_set_height(lv_obj_0, 308);
        lv_obj_set_flag(lv_obj_0, LV_OBJ_FLAG_SCROLLABLE, false);
        lv_obj_set_style_bg_color(lv_obj_0, lv_color_hex(0x181C1E), 0);
        lv_obj_set_style_bg_opa(lv_obj_0, (255 * 100 / 100), 0);
        lv_obj_set_style_pad_all(lv_obj_0, 0, 0);
        lv_obj_set_style_border_width(lv_obj_0, 1, 0);
        lv_obj_set_style_border_color(lv_obj_0, EDGE, 0);
        lv_obj_set_style_radius(lv_obj_0, 16, 0);
        lv_obj_set_style_shadow_width(lv_obj_0, 0, 0);
        lv_obj_set_style_shadow_opa(lv_obj_0, (255 * 25 / 100), 0);

        lv_obj_t * lv_label_0 = lv_label_create(lv_obj_0);
        lv_label_set_text(lv_label_0, "AMPLIFIERS");
        lv_obj_set_x(lv_label_0, 16);
        lv_obj_set_y(lv_label_0, 16);
        lv_obj_set_style_text_font(lv_label_0, font_14, 0);
        lv_obj_set_style_text_color(lv_label_0, MUTED, 0);

        lv_obj_t * voice_0 = amp_button_create(lv_obj_0, "");
        lv_obj_set_name(voice_0, "voice_0");
        lv_obj_set_x(voice_0, 10);
        lv_obj_set_y(voice_0, 46);
        lv_obj_set_width(voice_0, 400);
        lv_obj_set_height(voice_0, 76);
        lv_obj_set_style_bg_color(voice_0, lv_color_hex(0x202628), 0);
        lv_obj_set_style_bg_color(voice_0, SELECTED_BG, LV_STATE_CHECKED);
        lv_obj_set_style_border_color(voice_0, AMBER, LV_STATE_CHECKED);
        lv_obj_bind_state_if_eq(voice_0, &voice, LV_STATE_CHECKED, 0);
        lv_obj_add_subject_set_int_event(voice_0, &voice, LV_EVENT_CLICKED, 0);
        lv_obj_add_subject_set_int_event(voice_0, &edited, LV_EVENT_CLICKED, 1);
        lv_obj_t * lv_label_1 = lv_label_create(voice_0);
        lv_label_set_text(lv_label_1, "Fender");
        lv_obj_set_x(lv_label_1, 18);
        lv_obj_set_y(lv_label_1, 10);
        lv_obj_set_style_text_font(lv_label_1, font_14, 0);
        lv_obj_set_style_text_color(lv_label_1, MUTED, 0);

        lv_obj_t * lv_label_2 = lv_label_create(voice_0);
        lv_label_set_text(lv_label_2, "'65 Twin Reverb");
        lv_obj_set_x(lv_label_2, 18);
        lv_obj_set_y(lv_label_2, 32);
        lv_obj_set_style_text_font(lv_label_2, font_20, 0);
        lv_obj_set_style_text_color(lv_label_2, INK, 0);

        lv_obj_t * lv_obj_1 = lv_obj_create(voice_0);
        lv_obj_set_x(lv_obj_1, 0);
        lv_obj_set_y(lv_obj_1, 12);
        lv_obj_set_width(lv_obj_1, 4);
        lv_obj_set_height(lv_obj_1, 52);
        lv_obj_set_style_radius(lv_obj_1, 2, 0);
        lv_obj_set_style_bg_color(lv_obj_1, AMBER, 0);
        lv_obj_set_style_bg_opa(lv_obj_1, (255 * 100 / 100), 0);
        lv_obj_set_style_border_width(lv_obj_1, 0, 0);
        lv_obj_set_style_pad_all(lv_obj_1, 0, 0);
        lv_obj_set_flag(lv_obj_1, LV_OBJ_FLAG_SCROLLABLE, false);
        lv_obj_set_flag(lv_obj_1, LV_OBJ_FLAG_CLICKABLE, false);
        lv_obj_bind_flag_if_not_eq(lv_obj_1, &voice, LV_OBJ_FLAG_HIDDEN, 0);

        lv_obj_t * voice_1 = amp_button_create(lv_obj_0, "");
        lv_obj_set_name(voice_1, "voice_1");
        lv_obj_set_x(voice_1, 10);
        lv_obj_set_y(voice_1, 130);
        lv_obj_set_width(voice_1, 400);
        lv_obj_set_height(voice_1, 76);
        lv_obj_set_style_bg_color(voice_1, lv_color_hex(0x202628), 0);
        lv_obj_set_style_bg_color(voice_1, SELECTED_BG, LV_STATE_CHECKED);
        lv_obj_set_style_border_color(voice_1, AMBER, LV_STATE_CHECKED);
        lv_obj_bind_state_if_eq(voice_1, &voice, LV_STATE_CHECKED, 1);
        lv_obj_add_subject_set_int_event(voice_1, &voice, LV_EVENT_CLICKED, 1);
        lv_obj_add_subject_set_int_event(voice_1, &edited, LV_EVENT_CLICKED, 1);
        lv_obj_t * lv_label_3 = lv_label_create(voice_1);
        lv_label_set_text(lv_label_3, "Vox");
        lv_obj_set_x(lv_label_3, 18);
        lv_obj_set_y(lv_label_3, 10);
        lv_obj_set_style_text_font(lv_label_3, font_14, 0);
        lv_obj_set_style_text_color(lv_label_3, MUTED, 0);

        lv_obj_t * lv_label_4 = lv_label_create(voice_1);
        lv_label_set_text(lv_label_4, "AC30");
        lv_obj_set_x(lv_label_4, 18);
        lv_obj_set_y(lv_label_4, 32);
        lv_obj_set_style_text_font(lv_label_4, font_20, 0);
        lv_obj_set_style_text_color(lv_label_4, INK, 0);

        lv_obj_t * lv_obj_2 = lv_obj_create(voice_1);
        lv_obj_set_x(lv_obj_2, 0);
        lv_obj_set_y(lv_obj_2, 12);
        lv_obj_set_width(lv_obj_2, 4);
        lv_obj_set_height(lv_obj_2, 52);
        lv_obj_set_style_radius(lv_obj_2, 2, 0);
        lv_obj_set_style_bg_color(lv_obj_2, AMBER, 0);
        lv_obj_set_style_bg_opa(lv_obj_2, (255 * 100 / 100), 0);
        lv_obj_set_style_border_width(lv_obj_2, 0, 0);
        lv_obj_set_style_pad_all(lv_obj_2, 0, 0);
        lv_obj_set_flag(lv_obj_2, LV_OBJ_FLAG_SCROLLABLE, false);
        lv_obj_set_flag(lv_obj_2, LV_OBJ_FLAG_CLICKABLE, false);
        lv_obj_bind_flag_if_not_eq(lv_obj_2, &voice, LV_OBJ_FLAG_HIDDEN, 1);

        lv_obj_t * voice_2 = amp_button_create(lv_obj_0, "");
        lv_obj_set_name(voice_2, "voice_2");
        lv_obj_set_x(voice_2, 10);
        lv_obj_set_y(voice_2, 214);
        lv_obj_set_width(voice_2, 400);
        lv_obj_set_height(voice_2, 76);
        lv_obj_set_style_bg_color(voice_2, lv_color_hex(0x202628), 0);
        lv_obj_set_style_bg_color(voice_2, SELECTED_BG, LV_STATE_CHECKED);
        lv_obj_set_style_border_color(voice_2, AMBER, LV_STATE_CHECKED);
        lv_obj_bind_state_if_eq(voice_2, &voice, LV_STATE_CHECKED, 2);
        lv_obj_add_subject_set_int_event(voice_2, &voice, LV_EVENT_CLICKED, 2);
        lv_obj_add_subject_set_int_event(voice_2, &edited, LV_EVENT_CLICKED, 1);
        lv_obj_t * lv_label_5 = lv_label_create(voice_2);
        lv_label_set_text(lv_label_5, "Marshall");
        lv_obj_set_x(lv_label_5, 18);
        lv_obj_set_y(lv_label_5, 10);
        lv_obj_set_style_text_font(lv_label_5, font_14, 0);
        lv_obj_set_style_text_color(lv_label_5, MUTED, 0);

        lv_obj_t * lv_label_6 = lv_label_create(voice_2);
        lv_label_set_text(lv_label_6, "JCM800");
        lv_obj_set_x(lv_label_6, 18);
        lv_obj_set_y(lv_label_6, 32);
        lv_obj_set_style_text_font(lv_label_6, font_20, 0);
        lv_obj_set_style_text_color(lv_label_6, INK, 0);

        lv_obj_t * lv_obj_3 = lv_obj_create(voice_2);
        lv_obj_set_x(lv_obj_3, 0);
        lv_obj_set_y(lv_obj_3, 12);
        lv_obj_set_width(lv_obj_3, 4);
        lv_obj_set_height(lv_obj_3, 52);
        lv_obj_set_style_radius(lv_obj_3, 2, 0);
        lv_obj_set_style_bg_color(lv_obj_3, AMBER, 0);
        lv_obj_set_style_bg_opa(lv_obj_3, (255 * 100 / 100), 0);
        lv_obj_set_style_border_width(lv_obj_3, 0, 0);
        lv_obj_set_style_pad_all(lv_obj_3, 0, 0);
        lv_obj_set_flag(lv_obj_3, LV_OBJ_FLAG_SCROLLABLE, false);
        lv_obj_set_flag(lv_obj_3, LV_OBJ_FLAG_CLICKABLE, false);
        lv_obj_bind_flag_if_not_eq(lv_obj_3, &voice, LV_OBJ_FLAG_HIDDEN, 2);

        the_root = lv_obj_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

