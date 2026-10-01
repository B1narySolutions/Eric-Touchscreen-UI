/**
 * @file parameter_dial_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "parameter_dial_gen.h"
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

lv_obj_t * parameter_dial_create(lv_obj_t * parent, const char * title, lv_subject_t * subject, const char * format, int32_t minimum, int32_t maximum, int32_t step, int32_t negative_step, lv_color_t accent, int32_t control_id)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if AMP_EDITOR_CHECK_COMPILE_TARGET(AMP_EDITOR_TARGET_ALL)
    if (amp_editor_check_target(AMP_EDITOR_TARGET_ALL)) {
        lv_obj_t * lv_obj_0 = lv_obj_create(parent);
        lv_obj_set_name_static(lv_obj_0, "parameter_dial_#");
        lv_obj_set_width(lv_obj_0, 136);
        lv_obj_set_height(lv_obj_0, 228);
        lv_obj_set_flag(lv_obj_0, LV_OBJ_FLAG_SCROLLABLE, false);

        lv_obj_add_style(lv_obj_0, &surface, 0);
        lv_obj_t * lv_label_0 = lv_label_create(lv_obj_0);
        lv_label_set_text(lv_label_0, title);
        lv_obj_set_x(lv_label_0, 0);
        lv_obj_set_y(lv_label_0, 0);
        lv_obj_set_style_text_font(lv_label_0, font_16, 0);
        lv_obj_set_style_text_color(lv_label_0, MUTED, 0);
        lv_obj_set_align(lv_label_0, LV_ALIGN_TOP_MID);

        lv_obj_t * dial = lv_arc_create(lv_obj_0);
        lv_obj_set_name(dial, "dial");
        lv_obj_set_width(dial, 102);
        lv_obj_set_height(dial, 102);
        lv_obj_set_align(dial, LV_ALIGN_TOP_MID);
        lv_obj_set_y(dial, 30);
        lv_arc_set_rotation(dial, 135);
        lv_arc_set_bg_start_angle(dial, 0);
        lv_arc_set_bg_end_angle(dial, 270);
        lv_arc_set_min_value(dial, minimum);
        lv_arc_set_max_value(dial, maximum);
        lv_arc_bind_value(dial, subject);
        lv_obj_set_style_arc_color(dial, EDGE, 0);
        lv_obj_set_style_arc_width(dial, 7, 0);
        lv_obj_set_style_arc_color(dial, accent, LV_PART_INDICATOR);
        lv_obj_set_style_arc_width(dial, 7, LV_PART_INDICATOR);
        lv_obj_set_style_bg_color(dial, INK, LV_PART_KNOB);
        lv_obj_set_style_pad_all(dial, 3, LV_PART_KNOB);
        lv_obj_add_subject_set_int_event(dial, &edited, LV_EVENT_VALUE_CHANGED, 1);

        lv_obj_t * open_adjustment = lv_obj_create(lv_obj_0);
        lv_obj_set_name(open_adjustment, "open_adjustment");
        lv_obj_set_align(open_adjustment, LV_ALIGN_TOP_MID);
        lv_obj_set_y(open_adjustment, 53);
        lv_obj_set_width(open_adjustment, 54);
        lv_obj_set_height(open_adjustment, 54);
        lv_obj_set_flag(open_adjustment, LV_OBJ_FLAG_CLICKABLE, true);
        lv_obj_set_flag(open_adjustment, LV_OBJ_FLAG_SCROLLABLE, false);
        lv_obj_set_style_bg_opa(open_adjustment, (255 * 0 / 100), 0);
        lv_obj_set_style_border_width(open_adjustment, 0, 0);
        lv_obj_set_style_pad_all(open_adjustment, 0, 0);
        lv_obj_set_style_radius(open_adjustment, 0, 0);
        lv_obj_add_subject_set_int_event(open_adjustment, &active_adjustment, LV_EVENT_SHORT_CLICKED, control_id);

        lv_obj_t * readout = lv_label_create(lv_obj_0);
        lv_obj_set_name(readout, "readout");
        lv_obj_set_align(readout, LV_ALIGN_TOP_MID);
        lv_obj_set_y(readout, 136);
        lv_obj_set_size(readout, 112, 36);
        lv_obj_set_style_text_align(readout, LV_TEXT_ALIGN_CENTER, 0);
        lv_label_bind_text(readout, subject, format);
        lv_obj_set_style_text_font(readout, font_24, 0);
        lv_obj_set_style_text_color(readout, INK, 0);

        lv_obj_t * amp_button_0 = amp_button_create(lv_obj_0, "-");
        lv_obj_set_align(amp_button_0, LV_ALIGN_BOTTOM_MID);
        lv_obj_set_x(amp_button_0, -31);
        lv_obj_set_y(amp_button_0, -4);
        lv_obj_set_width(amp_button_0, 52);
        lv_obj_set_height(amp_button_0, 52);
        lv_subject_increment_dsc_t * subject_increment_event_0 = lv_obj_add_subject_increment_event(amp_button_0, subject, LV_EVENT_CLICKED, negative_step);
        lv_obj_set_subject_increment_event_min_value(amp_button_0, subject_increment_event_0, minimum);
        lv_obj_set_subject_increment_event_max_value(amp_button_0, subject_increment_event_0, maximum);
        lv_obj_add_subject_set_int_event(amp_button_0, &edited, LV_EVENT_CLICKED, 1);

        lv_obj_t * amp_button_1 = amp_button_create(lv_obj_0, "+");
        lv_obj_set_align(amp_button_1, LV_ALIGN_BOTTOM_MID);
        lv_obj_set_x(amp_button_1, 31);
        lv_obj_set_y(amp_button_1, -4);
        lv_obj_set_width(amp_button_1, 52);
        lv_obj_set_height(amp_button_1, 52);
        lv_subject_increment_dsc_t * subject_increment_event_1 = lv_obj_add_subject_increment_event(amp_button_1, subject, LV_EVENT_CLICKED, step);
        lv_obj_set_subject_increment_event_min_value(amp_button_1, subject_increment_event_1, minimum);
        lv_obj_set_subject_increment_event_max_value(amp_button_1, subject_increment_event_1, maximum);
        lv_obj_add_subject_set_int_event(amp_button_1, &edited, LV_EVENT_CLICKED, 1);

        lv_obj_t * open_readout = lv_obj_create(lv_obj_0);
        lv_obj_set_style_bg_opa(open_readout, (255 * 0 / 100), 0);
        lv_obj_set_style_border_width(open_readout, 0, 0);
        lv_obj_set_style_pad_all(open_readout, 0, 0);
        lv_obj_set_style_radius(open_readout, 0, 0);
        lv_obj_set_flag(open_readout, LV_OBJ_FLAG_SCROLLABLE, false);
        lv_obj_set_name(open_readout, "open_readout");
        lv_obj_set_align(open_readout, LV_ALIGN_TOP_MID);
        lv_obj_set_y(open_readout, 129);
        lv_obj_set_width(open_readout, lv_pct(100));
        lv_obj_set_height(open_readout, 37);
        lv_obj_set_flag(open_readout, LV_OBJ_FLAG_CLICKABLE, true);
        lv_obj_add_subject_set_int_event(open_readout, &active_adjustment, LV_EVENT_SHORT_CLICKED, control_id);

        the_root = lv_obj_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

