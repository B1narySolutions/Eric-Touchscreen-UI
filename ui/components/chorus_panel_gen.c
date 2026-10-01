/**
 * @file chorus_panel_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "chorus_panel_gen.h"
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

lv_obj_t * chorus_panel_create(lv_obj_t * parent)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if AMP_EDITOR_CHECK_COMPILE_TARGET(AMP_EDITOR_TARGET_ALL)
    if (amp_editor_check_target(AMP_EDITOR_TARGET_ALL)) {
        lv_obj_t * lv_obj_0 = lv_obj_create(parent);
        lv_obj_set_name_static(lv_obj_0, "chorus_panel_#");
        lv_obj_set_width(lv_obj_0, 992);
        lv_obj_set_height(lv_obj_0, 280);
        lv_obj_set_flag(lv_obj_0, LV_OBJ_FLAG_SCROLLABLE, false);

        lv_obj_add_style(lv_obj_0, &surface, 0);
        lv_obj_t * chorus_dial_0 = parameter_dial_create(lv_obj_0, "Mix", &chorus_p0, "%d%%", 0, 100, 1, -1, CHORUS, 14);
        lv_obj_set_name(chorus_dial_0, "chorus_dial_0");
        lv_obj_set_x(chorus_dial_0, 20);
        lv_obj_set_y(chorus_dial_0, 48);
        lv_obj_set_width(chorus_dial_0, 310);

        lv_obj_t * chorus_dial_1 = parameter_dial_create(lv_obj_0, "Rate (0.1 Hz)", &chorus_p1, "%d", 1, 100, 1, -1, CHORUS, 15);
        lv_obj_set_name(chorus_dial_1, "chorus_dial_1");
        lv_obj_set_x(chorus_dial_1, 342);
        lv_obj_set_y(chorus_dial_1, 48);
        lv_obj_set_width(chorus_dial_1, 310);

        lv_obj_t * chorus_dial_2 = parameter_dial_create(lv_obj_0, "Depth", &chorus_p2, "%d%%", 0, 100, 1, -1, CHORUS, 16);
        lv_obj_set_name(chorus_dial_2, "chorus_dial_2");
        lv_obj_set_x(chorus_dial_2, 664);
        lv_obj_set_y(chorus_dial_2, 48);
        lv_obj_set_width(chorus_dial_2, 310);

        lv_obj_t * lv_label_0 = lv_label_create(lv_obj_0);
        lv_label_set_text(lv_label_0, "CHORUS");
        lv_obj_set_x(lv_label_0, 20);
        lv_obj_set_y(lv_label_0, 16);
        lv_obj_set_style_text_font(lv_label_0, font_14, 0);
        lv_obj_set_style_text_color(lv_label_0, CHORUS, 0);

        lv_obj_t * lv_label_1 = lv_label_create(lv_obj_0);
        lv_label_set_text(lv_label_1, "ACTIVE");
        lv_obj_set_align(lv_label_1, LV_ALIGN_TOP_RIGHT);
        lv_obj_set_x(lv_label_1, -20);
        lv_obj_set_y(lv_label_1, 16);
        lv_obj_set_style_text_font(lv_label_1, font_14, 0);
        lv_obj_set_style_text_color(lv_label_1, MUTED, 0);
        lv_obj_bind_flag_if_not_eq(lv_label_1, &chorus_enabled, LV_OBJ_FLAG_HIDDEN, 1);

        lv_obj_t * lv_label_2 = lv_label_create(lv_obj_0);
        lv_label_set_text(lv_label_2, "BYPASSED");
        lv_obj_set_align(lv_label_2, LV_ALIGN_TOP_RIGHT);
        lv_obj_set_x(lv_label_2, -20);
        lv_obj_set_y(lv_label_2, 16);
        lv_obj_set_style_text_font(lv_label_2, font_14, 0);
        lv_obj_set_style_text_color(lv_label_2, MUTED, 0);
        lv_obj_bind_flag_if_not_eq(lv_label_2, &chorus_enabled, LV_OBJ_FLAG_HIDDEN, 0);

        the_root = lv_obj_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

