/**
 * @file drive_panel_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "drive_panel_gen.h"
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

lv_obj_t * drive_panel_create(lv_obj_t * parent)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if AMP_EDITOR_CHECK_COMPILE_TARGET(AMP_EDITOR_TARGET_ALL)
    if (amp_editor_check_target(AMP_EDITOR_TARGET_ALL)) {
        lv_obj_t * lv_obj_0 = lv_obj_create(parent);
        lv_obj_set_name_static(lv_obj_0, "drive_panel_#");
        lv_obj_set_width(lv_obj_0, 992);
        lv_obj_set_height(lv_obj_0, 280);
        lv_obj_set_flag(lv_obj_0, LV_OBJ_FLAG_SCROLLABLE, false);

        lv_obj_add_style(lv_obj_0, &surface, 0);
        lv_obj_t * drive_dial_0 = parameter_dial_create(lv_obj_0, "Level", &drive_p0, "%d%%", 0, 100, 1, -1, DRIVE, 6);
        lv_obj_set_name(drive_dial_0, "drive_dial_0");
        lv_obj_set_x(drive_dial_0, 20);
        lv_obj_set_y(drive_dial_0, 48);
        lv_obj_set_width(drive_dial_0, 310);

        lv_obj_t * drive_dial_1 = parameter_dial_create(lv_obj_0, "Gain", &drive_p1, "%d%%", 0, 100, 1, -1, DRIVE, 7);
        lv_obj_set_name(drive_dial_1, "drive_dial_1");
        lv_obj_set_x(drive_dial_1, 342);
        lv_obj_set_y(drive_dial_1, 48);
        lv_obj_set_width(drive_dial_1, 310);

        lv_obj_t * drive_dial_2 = parameter_dial_create(lv_obj_0, "Tone", &drive_p2, "%d%%", 0, 100, 1, -1, DRIVE, 8);
        lv_obj_set_name(drive_dial_2, "drive_dial_2");
        lv_obj_set_x(drive_dial_2, 664);
        lv_obj_set_y(drive_dial_2, 48);
        lv_obj_set_width(drive_dial_2, 310);

        lv_obj_t * lv_label_0 = lv_label_create(lv_obj_0);
        lv_label_set_text(lv_label_0, "DRIVE");
        lv_obj_set_x(lv_label_0, 20);
        lv_obj_set_y(lv_label_0, 16);
        lv_obj_set_style_text_font(lv_label_0, font_14, 0);
        lv_obj_set_style_text_color(lv_label_0, DRIVE, 0);

        lv_obj_t * lv_label_1 = lv_label_create(lv_obj_0);
        lv_label_set_text(lv_label_1, "ACTIVE");
        lv_obj_set_align(lv_label_1, LV_ALIGN_TOP_RIGHT);
        lv_obj_set_x(lv_label_1, -20);
        lv_obj_set_y(lv_label_1, 16);
        lv_obj_set_style_text_font(lv_label_1, font_14, 0);
        lv_obj_set_style_text_color(lv_label_1, MUTED, 0);
        lv_obj_bind_flag_if_not_eq(lv_label_1, &drive_enabled, LV_OBJ_FLAG_HIDDEN, 1);

        lv_obj_t * lv_label_2 = lv_label_create(lv_obj_0);
        lv_label_set_text(lv_label_2, "BYPASSED");
        lv_obj_set_align(lv_label_2, LV_ALIGN_TOP_RIGHT);
        lv_obj_set_x(lv_label_2, -20);
        lv_obj_set_y(lv_label_2, 16);
        lv_obj_set_style_text_font(lv_label_2, font_14, 0);
        lv_obj_set_style_text_color(lv_label_2, MUTED, 0);
        lv_obj_bind_flag_if_not_eq(lv_label_2, &drive_enabled, LV_OBJ_FLAG_HIDDEN, 0);

        the_root = lv_obj_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

