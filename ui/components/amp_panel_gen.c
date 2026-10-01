/**
 * @file amp_panel_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "amp_panel_gen.h"
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

lv_obj_t * amp_panel_create(lv_obj_t * parent)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if AMP_EDITOR_CHECK_COMPILE_TARGET(AMP_EDITOR_TARGET_ALL)
    if (amp_editor_check_target(AMP_EDITOR_TARGET_ALL)) {
        lv_obj_t * lv_obj_0 = lv_obj_create(parent);
        lv_obj_set_name_static(lv_obj_0, "amp_panel_#");
        lv_obj_set_width(lv_obj_0, 992);
        lv_obj_set_height(lv_obj_0, 280);
        lv_obj_set_flag(lv_obj_0, LV_OBJ_FLAG_SCROLLABLE, false);

        lv_obj_add_style(lv_obj_0, &surface, 0);
        lv_obj_t * amp_dial_0 = parameter_dial_create(lv_obj_0, "Gain", &amp_p0, "%d%%", 0, 100, 1, -1, AMP, 9);
        lv_obj_set_name(amp_dial_0, "amp_dial_0");
        lv_obj_set_x(amp_dial_0, 20);
        lv_obj_set_y(amp_dial_0, 48);
        lv_obj_set_width(amp_dial_0, 180);

        lv_obj_t * amp_dial_1 = parameter_dial_create(lv_obj_0, "Bass", &amp_p1, "%d%%", 0, 100, 1, -1, AMP, 10);
        lv_obj_set_name(amp_dial_1, "amp_dial_1");
        lv_obj_set_x(amp_dial_1, 212);
        lv_obj_set_y(amp_dial_1, 48);
        lv_obj_set_width(amp_dial_1, 180);

        lv_obj_t * amp_dial_2 = parameter_dial_create(lv_obj_0, "Middle", &amp_p2, "%d%%", 0, 100, 1, -1, AMP, 11);
        lv_obj_set_name(amp_dial_2, "amp_dial_2");
        lv_obj_set_x(amp_dial_2, 404);
        lv_obj_set_y(amp_dial_2, 48);
        lv_obj_set_width(amp_dial_2, 180);

        lv_obj_t * amp_dial_3 = parameter_dial_create(lv_obj_0, "Treble", &amp_p3, "%d%%", 0, 100, 1, -1, AMP, 12);
        lv_obj_set_name(amp_dial_3, "amp_dial_3");
        lv_obj_set_x(amp_dial_3, 596);
        lv_obj_set_y(amp_dial_3, 48);
        lv_obj_set_width(amp_dial_3, 180);

        lv_obj_t * amp_dial_4 = parameter_dial_create(lv_obj_0, "Level", &amp_p4, "%d%%", 0, 100, 1, -1, AMP, 13);
        lv_obj_set_name(amp_dial_4, "amp_dial_4");
        lv_obj_set_x(amp_dial_4, 788);
        lv_obj_set_y(amp_dial_4, 48);
        lv_obj_set_width(amp_dial_4, 180);

        lv_obj_t * lv_label_0 = lv_label_create(lv_obj_0);
        lv_label_set_text(lv_label_0, "AMP TONE");
        lv_obj_set_x(lv_label_0, 20);
        lv_obj_set_y(lv_label_0, 16);
        lv_obj_set_style_text_font(lv_label_0, font_14, 0);
        lv_obj_set_style_text_color(lv_label_0, AMP, 0);

        the_root = lv_obj_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

