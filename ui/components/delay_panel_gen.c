/**
 * @file delay_panel_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "delay_panel_gen.h"
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

lv_obj_t * delay_panel_create(lv_obj_t * parent)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if AMP_EDITOR_CHECK_COMPILE_TARGET(AMP_EDITOR_TARGET_ALL)
    if (amp_editor_check_target(AMP_EDITOR_TARGET_ALL)) {
        lv_obj_t * lv_obj_0 = lv_obj_create(parent);
        lv_obj_set_name_static(lv_obj_0, "delay_panel_#");
        lv_obj_set_width(lv_obj_0, 992);
        lv_obj_set_height(lv_obj_0, 280);
        lv_obj_set_flag(lv_obj_0, LV_OBJ_FLAG_SCROLLABLE, false);

        lv_obj_add_style(lv_obj_0, &surface, 0);
        lv_obj_t * delay_dial_0 = parameter_dial_create(lv_obj_0, "Mix", &delay_p0, "%d%%", 0, 100, 1, -1, DELAY, 17);
        lv_obj_set_name(delay_dial_0, "delay_dial_0");
        lv_obj_set_x(delay_dial_0, 20);
        lv_obj_set_y(delay_dial_0, 48);
        lv_obj_set_width(delay_dial_0, 310);

        lv_obj_t * delay_dial_1 = parameter_dial_create(lv_obj_0, "Time", &delay_p1, "%d ms", 20, 1500, 10, -10, DELAY, 18);
        lv_obj_set_name(delay_dial_1, "delay_dial_1");
        lv_obj_set_x(delay_dial_1, 342);
        lv_obj_set_y(delay_dial_1, 48);
        lv_obj_set_width(delay_dial_1, 310);

        lv_obj_t * delay_dial_2 = parameter_dial_create(lv_obj_0, "Feedback", &delay_p2, "%d%%", 0, 95, 1, -1, DELAY, 19);
        lv_obj_set_name(delay_dial_2, "delay_dial_2");
        lv_obj_set_x(delay_dial_2, 664);
        lv_obj_set_y(delay_dial_2, 48);
        lv_obj_set_width(delay_dial_2, 310);

        lv_obj_t * lv_label_0 = lv_label_create(lv_obj_0);
        lv_label_set_text(lv_label_0, "DELAY");
        lv_obj_set_x(lv_label_0, 20);
        lv_obj_set_y(lv_label_0, 16);
        lv_obj_set_style_text_font(lv_label_0, font_14, 0);
        lv_obj_set_style_text_color(lv_label_0, DELAY, 0);

        lv_obj_t * lv_label_1 = lv_label_create(lv_obj_0);
        lv_label_set_text(lv_label_1, "ACTIVE");
        lv_obj_set_align(lv_label_1, LV_ALIGN_TOP_RIGHT);
        lv_obj_set_x(lv_label_1, -20);
        lv_obj_set_y(lv_label_1, 16);
        lv_obj_set_style_text_font(lv_label_1, font_14, 0);
        lv_obj_set_style_text_color(lv_label_1, MUTED, 0);
        lv_obj_bind_flag_if_not_eq(lv_label_1, &delay_enabled, LV_OBJ_FLAG_HIDDEN, 1);

        lv_obj_t * lv_label_2 = lv_label_create(lv_obj_0);
        lv_label_set_text(lv_label_2, "BYPASSED");
        lv_obj_set_align(lv_label_2, LV_ALIGN_TOP_RIGHT);
        lv_obj_set_x(lv_label_2, -20);
        lv_obj_set_y(lv_label_2, 16);
        lv_obj_set_style_text_font(lv_label_2, font_14, 0);
        lv_obj_set_style_text_color(lv_label_2, MUTED, 0);
        lv_obj_bind_flag_if_not_eq(lv_label_2, &delay_enabled, LV_OBJ_FLAG_HIDDEN, 0);

        the_root = lv_obj_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

