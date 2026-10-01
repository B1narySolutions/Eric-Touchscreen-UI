/** @file cabinet_panel_gen.c */
#include "cabinet_panel_gen.h"
#include "../amp_editor.h"

static lv_obj_t * make_ir_button(lv_obj_t * parent, const char * name, const char * text,
                                 int32_t x, int32_t value)
{
    lv_obj_t * button = amp_button_create(parent, text);
    lv_obj_set_name(button, name);
    lv_obj_set_pos(button, x, 92);
    lv_obj_set_size(button, 300, 112);
    lv_obj_set_style_bg_color(button, SELECTED_BG, LV_STATE_CHECKED);
    lv_obj_set_style_border_color(button, CABINET, LV_STATE_CHECKED);
    lv_obj_set_style_text_color(button, CABINET, LV_STATE_CHECKED);
    lv_obj_bind_state_if_eq(button, &cabinet_ir, LV_STATE_CHECKED, value);
    lv_obj_add_subject_set_int_event(button, &cabinet_ir, LV_EVENT_CLICKED, value);
    lv_obj_add_subject_set_int_event(button, &edited, LV_EVENT_CLICKED, 1);
    return button;
}

lv_obj_t * cabinet_panel_create(lv_obj_t * parent)
{
    lv_obj_t * root = lv_obj_create(parent);
    lv_obj_set_name_static(root, "cabinet_panel_#");
    lv_obj_set_size(root, 992, 280);
    lv_obj_remove_flag(root, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_style(root, &surface, 0);

    lv_obj_t * title = lv_label_create(root);
    lv_label_set_text(title, "CABINET / IMPULSE RESPONSE");
    lv_obj_set_pos(title, 20, 16);
    lv_obj_set_style_text_font(title, font_14, 0);
    lv_obj_set_style_text_color(title, CABINET, 0);

    lv_obj_t * description = lv_label_create(root);
    lv_label_set_text(description, "Select the cabinet IR EQ curve applied at the end of the signal chain.");
    lv_obj_set_pos(description, 20, 48);
    lv_obj_set_style_text_font(description, font_16, 0);
    lv_obj_set_style_text_color(description, MUTED, 0);

    make_ir_button(root, "cabinet_ir_0", "1x12 OPEN BACK", 20, 0);
    make_ir_button(root, "cabinet_ir_1", "2x12 ALNICO BLUE", 346, 1);
    make_ir_button(root, "cabinet_ir_2", "4x12 VINTAGE", 672, 2);

    lv_obj_t * active = lv_label_create(root);
    lv_label_set_text(active, "CABINET ACTIVE");
    lv_obj_set_pos(active, 20, 238);
    lv_obj_set_style_text_font(active, font_14, 0);
    lv_obj_set_style_text_color(active, CABINET, 0);
    lv_obj_bind_flag_if_not_eq(active, &cabinet_enabled, LV_OBJ_FLAG_HIDDEN, 1);

    lv_obj_t * bypassed = lv_label_create(root);
    lv_label_set_text(bypassed, "CABINET BYPASSED");
    lv_obj_set_pos(bypassed, 20, 238);
    lv_obj_set_style_text_font(bypassed, font_14, 0);
    lv_obj_set_style_text_color(bypassed, MUTED, 0);
    lv_obj_bind_flag_if_not_eq(bypassed, &cabinet_enabled, LV_OBJ_FLAG_HIDDEN, 0);
    return root;
}
