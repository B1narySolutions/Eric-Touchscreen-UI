/**
 * @file home_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "home_gen.h"
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

lv_obj_t * home_create(void)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if AMP_EDITOR_CHECK_COMPILE_TARGET(AMP_EDITOR_TARGET_ALL)
    if (amp_editor_check_target(AMP_EDITOR_TARGET_ALL)) {
        lv_obj_t * lv_obj_0 = lv_obj_create(NULL);
        lv_obj_set_name_static(lv_obj_0, "home_#");
        lv_obj_set_width(lv_obj_0, 1024);
        lv_obj_set_height(lv_obj_0, 600);
        lv_obj_set_flag(lv_obj_0, LV_OBJ_FLAG_SCROLLABLE, false);
        lv_obj_set_style_bg_color(lv_obj_0, BACKGROUND, 0);
        lv_obj_set_style_bg_opa(lv_obj_0, (255 * 100 / 100), 0);
        lv_obj_set_style_pad_all(lv_obj_0, 0, 0);
        lv_obj_set_style_border_width(lv_obj_0, 0, 0);
        lv_obj_set_style_radius(lv_obj_0, 0, 0);
        lv_obj_set_style_text_font(lv_obj_0, font_16, 0);
        lv_obj_set_style_text_color(lv_obj_0, INK, 0);

        lv_obj_t * preset_name = lv_label_create(lv_obj_0);
        lv_obj_set_name(preset_name, "preset_name");
        lv_obj_set_x(preset_name, 24);
        lv_obj_set_y(preset_name, 25);
        lv_label_bind_text(preset_name, &preset_number, "Preset %d");
        lv_obj_set_style_text_font(preset_name, font_24, 0);

        lv_obj_t * lv_label_0 = lv_label_create(lv_obj_0);
        lv_label_set_text(lv_label_0, "PREVIEW");
        lv_obj_set_x(lv_label_0, 25);
        lv_obj_set_y(lv_label_0, 56);
        lv_obj_set_style_text_font(lv_label_0, font_14, 0);
        lv_obj_set_style_text_color(lv_label_0, MUTED, 0);
        lv_obj_bind_flag_if_not_eq(lv_label_0, &edited, LV_OBJ_FLAG_HIDDEN, 0);

        lv_obj_t * lv_label_1 = lv_label_create(lv_obj_0);
        lv_label_set_text(lv_label_1, "EDITED");
        lv_obj_set_x(lv_label_1, 25);
        lv_obj_set_y(lv_label_1, 56);
        lv_obj_set_style_text_font(lv_label_1, font_14, 0);
        lv_obj_set_style_text_color(lv_label_1, AMBER, 0);
        lv_obj_bind_flag_if_not_eq(lv_label_1, &edited, LV_OBJ_FLAG_HIDDEN, 1);

        lv_obj_t * amp_button_0 = amp_button_create(lv_obj_0, "Save");
        lv_obj_set_x(amp_button_0, 660);
        lv_obj_set_y(amp_button_0, 20);
        lv_obj_set_width(amp_button_0, 98);
        lv_obj_set_height(amp_button_0, 56);
        lv_obj_set_style_bg_color(amp_button_0, SELECTED_BG, 0);
        lv_obj_add_subject_set_int_event(amp_button_0, &dialog, LV_EVENT_CLICKED, 3);

        lv_obj_t * lv_label_2 = lv_label_create(lv_obj_0);
        lv_label_set_text(lv_label_2, "UI PROTOTYPE");
        lv_obj_set_x(lv_label_2, 804);
        lv_obj_set_y(lv_label_2, 26);
        lv_obj_set_style_text_font(lv_label_2, font_14, 0);
        lv_obj_set_style_text_color(lv_label_2, MUTED, 0);

        lv_obj_t * lv_label_3 = lv_label_create(lv_obj_0);
        lv_label_set_text(lv_label_3, "BAT -- / OFFLINE");
        lv_obj_set_x(lv_label_3, 804);
        lv_obj_set_y(lv_label_3, 50);
        lv_obj_set_style_text_font(lv_label_3, font_14, 0);
        lv_obj_set_style_text_color(lv_label_3, MUTED, 0);

        lv_obj_t * effect_chain = lv_obj_create(lv_obj_0);
        lv_obj_set_name(effect_chain, "effect_chain");
        lv_obj_set_pos(effect_chain, 16, 94);
        lv_obj_set_size(effect_chain, 984, 128);
        lv_obj_remove_flag(effect_chain, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_remove_flag(effect_chain, LV_OBJ_FLAG_CLICKABLE);
        lv_obj_set_style_bg_opa(effect_chain, LV_OPA_TRANSP, 0);
        lv_obj_set_style_border_width(effect_chain, 0, 0);
        lv_obj_set_style_pad_all(effect_chain, 0, 0);
        lv_obj_set_style_radius(effect_chain, 0, 0);

        lv_obj_t * movable_effects = lv_obj_create(effect_chain);
        lv_obj_set_name(movable_effects, "movable_effects");
        lv_obj_set_pos(movable_effects, 0, 0);
        lv_obj_set_size(movable_effects, 851, 128);
        lv_obj_remove_flag(movable_effects, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_remove_flag(movable_effects, LV_OBJ_FLAG_CLICKABLE);
        lv_obj_set_style_bg_opa(movable_effects, LV_OPA_TRANSP, 0);
        lv_obj_set_style_border_width(movable_effects, 0, 0);
        lv_obj_set_style_pad_all(movable_effects, 0, 0);
        lv_obj_set_style_radius(movable_effects, 0, 0);
        lv_obj_add_subject_set_int_event(movable_effects, &edited, LV_EVENT_VALUE_CHANGED, 1);
        lv_obj_add_event_cb(movable_effects, amp_chain_lifecycle_event, LV_EVENT_ALL, NULL);

        lv_obj_t * gate_block = signal_block_create(movable_effects, "GATE", 0, &gate_enabled, GATE);
        lv_obj_set_name(gate_block, "gate_block");
        lv_obj_set_pos(gate_block, 0, 0);
        lv_obj_t * comp_block = signal_block_create(movable_effects, "COMP", 1, &comp_enabled, COMP);
        lv_obj_set_name(comp_block, "comp_block");
        lv_obj_set_pos(comp_block, 123, 0);
        lv_obj_t * drive_block = signal_block_create(movable_effects, "DRIVE", 2, &drive_enabled, DRIVE);
        lv_obj_set_name(drive_block, "drive_block");
        lv_obj_set_pos(drive_block, 246, 0);
        lv_obj_t * amp_block = signal_block_create(movable_effects, "AMP", 3, &amp_enabled, AMP);
        lv_obj_set_name(amp_block, "amp_block");
        lv_obj_set_pos(amp_block, 369, 0);
        lv_obj_t * chorus_block = signal_block_create(movable_effects, "CHORUS", 4, &chorus_enabled, CHORUS);
        lv_obj_set_name(chorus_block, "chorus_block");
        lv_obj_set_pos(chorus_block, 492, 0);
        lv_obj_t * delay_block = signal_block_create(movable_effects, "DELAY", 5, &delay_enabled, DELAY);
        lv_obj_set_name(delay_block, "delay_block");
        lv_obj_set_pos(delay_block, 615, 0);
        lv_obj_t * reverb_block = signal_block_create(movable_effects, "REVERB", 6, &reverb_enabled, REVERB);
        lv_obj_set_name(reverb_block, "reverb_block");
        lv_obj_set_pos(reverb_block, 738, 0);

        lv_obj_t * cabinet_block = signal_block_create(effect_chain, "CAB", 7, &cabinet_enabled, CABINET);
        lv_obj_set_name(cabinet_block, "cabinet_block");
        lv_obj_set_pos(cabinet_block, 861, 0);

        lv_obj_t * gate_editor = gate_panel_create(lv_obj_0);
        lv_obj_set_name(gate_editor, "gate_editor");
        lv_obj_set_x(gate_editor, 16);
        lv_obj_set_y(gate_editor, 236);
        lv_obj_bind_flag_if_not_eq(gate_editor, &selected_block, LV_OBJ_FLAG_HIDDEN, 0);

        lv_obj_t * comp_editor = comp_panel_create(lv_obj_0);
        lv_obj_set_name(comp_editor, "comp_editor");
        lv_obj_set_x(comp_editor, 16);
        lv_obj_set_y(comp_editor, 236);
        lv_obj_bind_flag_if_not_eq(comp_editor, &selected_block, LV_OBJ_FLAG_HIDDEN, 1);

        lv_obj_t * drive_editor = drive_panel_create(lv_obj_0);
        lv_obj_set_name(drive_editor, "drive_editor");
        lv_obj_set_x(drive_editor, 16);
        lv_obj_set_y(drive_editor, 236);
        lv_obj_bind_flag_if_not_eq(drive_editor, &selected_block, LV_OBJ_FLAG_HIDDEN, 2);

        lv_obj_t * amp_editor = amp_panel_create(lv_obj_0);
        lv_obj_set_name(amp_editor, "amp_editor");
        lv_obj_set_x(amp_editor, 16);
        lv_obj_set_y(amp_editor, 236);
        lv_obj_bind_flag_if_not_eq(amp_editor, &selected_block, LV_OBJ_FLAG_HIDDEN, 3);

        lv_obj_t * chorus_editor = chorus_panel_create(lv_obj_0);
        lv_obj_set_name(chorus_editor, "chorus_editor");
        lv_obj_set_x(chorus_editor, 16);
        lv_obj_set_y(chorus_editor, 236);
        lv_obj_bind_flag_if_not_eq(chorus_editor, &selected_block, LV_OBJ_FLAG_HIDDEN, 4);

        lv_obj_t * delay_editor = delay_panel_create(lv_obj_0);
        lv_obj_set_name(delay_editor, "delay_editor");
        lv_obj_set_x(delay_editor, 16);
        lv_obj_set_y(delay_editor, 236);
        lv_obj_bind_flag_if_not_eq(delay_editor, &selected_block, LV_OBJ_FLAG_HIDDEN, 5);

        lv_obj_t * reverb_editor = reverb_panel_create(lv_obj_0);
        lv_obj_set_name(reverb_editor, "reverb_editor");
        lv_obj_set_x(reverb_editor, 16);
        lv_obj_set_y(reverb_editor, 236);
        lv_obj_bind_flag_if_not_eq(reverb_editor, &selected_block, LV_OBJ_FLAG_HIDDEN, 6);

        lv_obj_t * cabinet_editor = cabinet_panel_create(lv_obj_0);
        lv_obj_set_name(cabinet_editor, "cabinet_editor");
        lv_obj_set_pos(cabinet_editor, 16, 236);
        lv_obj_bind_flag_if_not_eq(cabinet_editor, &selected_block, LV_OBJ_FLAG_HIDDEN, 7);

        lv_obj_t * amp_button_1 = amp_button_create(lv_obj_0, "Presets");
        lv_obj_set_x(amp_button_1, 24);
        lv_obj_set_y(amp_button_1, 534);
        lv_obj_set_width(amp_button_1, 142);
        lv_obj_set_height(amp_button_1, 54);
        lv_obj_add_subject_set_int_event(amp_button_1, &dialog, LV_EVENT_CLICKED, 1);

        lv_obj_t * amp_button_2 = amp_button_create(lv_obj_0, "Settings");
        lv_obj_set_x(amp_button_2, 178);
        lv_obj_set_y(amp_button_2, 534);
        lv_obj_set_width(amp_button_2, 142);
        lv_obj_set_height(amp_button_2, 54);
        lv_obj_add_subject_set_int_event(amp_button_2, &dialog, LV_EVENT_CLICKED, 2);

        lv_obj_t * lv_label_4 = lv_label_create(lv_obj_0);
        lv_label_set_text(lv_label_4, "MASTER");
        lv_obj_set_x(lv_label_4, 372);
        lv_obj_set_y(lv_label_4, 552);
        lv_obj_set_style_text_font(lv_label_4, font_14, 0);
        lv_obj_set_style_text_color(lv_label_4, MUTED, 0);

        lv_obj_t * master_volume = lv_slider_create(lv_obj_0);
        lv_obj_set_name(master_volume, "master_volume");
        lv_obj_set_x(master_volume, 470);
        lv_obj_set_y(master_volume, 556);
        lv_obj_set_width(master_volume, 290);
        lv_obj_set_height(master_volume, 10);
        lv_slider_bind_value(master_volume, &master);
        lv_slider_set_min_value(master_volume, 0);
        lv_slider_set_max_value(master_volume, 100);
        lv_obj_set_ext_click_area(master_volume, 22);
        lv_obj_set_style_bg_color(master_volume, EDGE, 0);
        lv_obj_set_style_bg_color(master_volume, AMBER, LV_PART_INDICATOR);
        lv_obj_set_style_bg_color(master_volume, INK, LV_PART_KNOB);
        lv_obj_add_subject_set_int_event(master_volume, &edited, LV_EVENT_VALUE_CHANGED, 1);

        lv_obj_t * lv_label_5 = lv_label_create(lv_obj_0);
        lv_obj_set_x(lv_label_5, 792);
        lv_obj_set_y(lv_label_5, 550);
        lv_label_bind_text(lv_label_5, &master, "%d%%");
        lv_obj_set_style_text_font(lv_label_5, font_24, 0);

        lv_obj_t * amp_button_3 = amp_button_create(lv_obj_0, "");
        lv_obj_set_x(amp_button_3, 880);
        lv_obj_set_y(amp_button_3, 534);
        lv_obj_set_width(amp_button_3, 120);
        lv_obj_set_height(amp_button_3, 54);
        lv_obj_set_style_border_color(amp_button_3, lv_color_hex(0xEA8C83), LV_STATE_CHECKED);
        lv_obj_add_subject_toggle_event(amp_button_3, &muted_output, LV_EVENT_CLICKED);
        lv_obj_bind_state_if_eq(amp_button_3, &muted_output, LV_STATE_CHECKED, 1);
        lv_obj_t * lv_label_6 = lv_label_create(amp_button_3);
        lv_label_set_text(lv_label_6, "MUTE");
        lv_obj_set_x(lv_label_6, 0);
        lv_obj_set_y(lv_label_6, 0);
        lv_obj_set_style_text_font(lv_label_6, font_16, 0);
        lv_obj_set_style_text_color(lv_label_6, INK, 0);
        lv_obj_set_align(lv_label_6, LV_ALIGN_CENTER);
        lv_obj_bind_flag_if_not_eq(lv_label_6, &muted_output, LV_OBJ_FLAG_HIDDEN, 0);

        lv_obj_t * lv_label_7 = lv_label_create(amp_button_3);
        lv_label_set_text(lv_label_7, "UNMUTE");
        lv_obj_set_x(lv_label_7, 0);
        lv_obj_set_y(lv_label_7, 0);
        lv_obj_set_style_text_font(lv_label_7, font_16, 0);
        lv_obj_set_style_text_color(lv_label_7, INK, 0);
        lv_obj_set_align(lv_label_7, LV_ALIGN_CENTER);
        lv_obj_bind_flag_if_not_eq(lv_label_7, &muted_output, LV_OBJ_FLAG_HIDDEN, 1);

        lv_obj_t * open_master = lv_obj_create(lv_obj_0);
        lv_obj_set_style_bg_opa(open_master, (255 * 0 / 100), 0);
        lv_obj_set_style_border_width(open_master, 0, 0);
        lv_obj_set_style_pad_all(open_master, 0, 0);
        lv_obj_set_style_radius(open_master, 0, 0);
        lv_obj_set_flag(open_master, LV_OBJ_FLAG_SCROLLABLE, false);
        lv_obj_set_name(open_master, "open_master");
        lv_obj_set_x(open_master, 366);
        lv_obj_set_y(open_master, 534);
        lv_obj_set_width(open_master, 76);
        lv_obj_set_height(open_master, 54);
        lv_obj_set_flag(open_master, LV_OBJ_FLAG_CLICKABLE, true);
        lv_obj_add_subject_set_int_event(open_master, &active_adjustment, LV_EVENT_SHORT_CLICKED, 100);

        lv_obj_t * open_master_readout = lv_obj_create(lv_obj_0);
        lv_obj_set_style_bg_opa(open_master_readout, (255 * 0 / 100), 0);
        lv_obj_set_style_border_width(open_master_readout, 0, 0);
        lv_obj_set_style_pad_all(open_master_readout, 0, 0);
        lv_obj_set_style_radius(open_master_readout, 0, 0);
        lv_obj_set_flag(open_master_readout, LV_OBJ_FLAG_SCROLLABLE, false);
        lv_obj_set_name(open_master_readout, "open_master_readout");
        lv_obj_set_x(open_master_readout, 788);
        lv_obj_set_y(open_master_readout, 534);
        lv_obj_set_width(open_master_readout, 76);
        lv_obj_set_height(open_master_readout, 54);
        lv_obj_set_flag(open_master_readout, LV_OBJ_FLAG_CLICKABLE, true);
        lv_obj_add_subject_set_int_event(open_master_readout, &active_adjustment, LV_EVENT_SHORT_CLICKED, 100);

        lv_obj_t * amplifier_drawer = amp_drawer_create(lv_obj_0);
        lv_obj_set_name(amplifier_drawer, "amplifier_drawer");

        lv_obj_t * dialogs = preview_dialogs_create(lv_obj_0);
        lv_obj_set_name(dialogs, "dialogs");

        lv_obj_t * adjustment_1 = adjustment_popup_create(lv_obj_0, 1, "Threshold", &gate_p0, "%d dB", -80, 0, GATE);
        lv_obj_set_name(adjustment_1, "adjustment_1");

        lv_obj_t * adjustment_2 = adjustment_popup_create(lv_obj_0, 2, "Release", &gate_p1, "%d ms", 10, 500, GATE);
        lv_obj_set_name(adjustment_2, "adjustment_2");

        lv_obj_t * adjustment_3 = adjustment_popup_create(lv_obj_0, 3, "Level", &comp_p0, "%d%%", 0, 100, COMP);
        lv_obj_set_name(adjustment_3, "adjustment_3");

        lv_obj_t * adjustment_4 = adjustment_popup_create(lv_obj_0, 4, "Attack", &comp_p1, "%d ms", 1, 100, COMP);
        lv_obj_set_name(adjustment_4, "adjustment_4");

        lv_obj_t * adjustment_5 = adjustment_popup_create(lv_obj_0, 5, "Sustain", &comp_p2, "%d%%", 0, 100, COMP);
        lv_obj_set_name(adjustment_5, "adjustment_5");

        lv_obj_t * adjustment_6 = adjustment_popup_create(lv_obj_0, 6, "Level", &drive_p0, "%d%%", 0, 100, DRIVE);
        lv_obj_set_name(adjustment_6, "adjustment_6");

        lv_obj_t * adjustment_7 = adjustment_popup_create(lv_obj_0, 7, "Gain", &drive_p1, "%d%%", 0, 100, DRIVE);
        lv_obj_set_name(adjustment_7, "adjustment_7");

        lv_obj_t * adjustment_8 = adjustment_popup_create(lv_obj_0, 8, "Tone", &drive_p2, "%d%%", 0, 100, DRIVE);
        lv_obj_set_name(adjustment_8, "adjustment_8");

        lv_obj_t * adjustment_9 = adjustment_popup_create(lv_obj_0, 9, "Gain", &amp_p0, "%d%%", 0, 100, AMP);
        lv_obj_set_name(adjustment_9, "adjustment_9");

        lv_obj_t * adjustment_10 = adjustment_popup_create(lv_obj_0, 10, "Bass", &amp_p1, "%d%%", 0, 100, AMP);
        lv_obj_set_name(adjustment_10, "adjustment_10");

        lv_obj_t * adjustment_11 = adjustment_popup_create(lv_obj_0, 11, "Middle", &amp_p2, "%d%%", 0, 100, AMP);
        lv_obj_set_name(adjustment_11, "adjustment_11");

        lv_obj_t * adjustment_12 = adjustment_popup_create(lv_obj_0, 12, "Treble", &amp_p3, "%d%%", 0, 100, AMP);
        lv_obj_set_name(adjustment_12, "adjustment_12");

        lv_obj_t * adjustment_13 = adjustment_popup_create(lv_obj_0, 13, "Level", &amp_p4, "%d%%", 0, 100, AMP);
        lv_obj_set_name(adjustment_13, "adjustment_13");

        lv_obj_t * adjustment_14 = adjustment_popup_create(lv_obj_0, 14, "Mix", &chorus_p0, "%d%%", 0, 100, CHORUS);
        lv_obj_set_name(adjustment_14, "adjustment_14");

        lv_obj_t * adjustment_15 = adjustment_popup_create(lv_obj_0, 15, "Rate (0.1 Hz)", &chorus_p1, "%d", 1, 100, CHORUS);
        lv_obj_set_name(adjustment_15, "adjustment_15");

        lv_obj_t * adjustment_16 = adjustment_popup_create(lv_obj_0, 16, "Depth", &chorus_p2, "%d%%", 0, 100, CHORUS);
        lv_obj_set_name(adjustment_16, "adjustment_16");

        lv_obj_t * adjustment_17 = adjustment_popup_create(lv_obj_0, 17, "Mix", &delay_p0, "%d%%", 0, 100, DELAY);
        lv_obj_set_name(adjustment_17, "adjustment_17");

        lv_obj_t * adjustment_18 = adjustment_popup_create(lv_obj_0, 18, "Time", &delay_p1, "%d ms", 20, 1500, DELAY);
        lv_obj_set_name(adjustment_18, "adjustment_18");

        lv_obj_t * adjustment_19 = adjustment_popup_create(lv_obj_0, 19, "Feedback", &delay_p2, "%d%%", 0, 95, DELAY);
        lv_obj_set_name(adjustment_19, "adjustment_19");

        lv_obj_t * adjustment_20 = adjustment_popup_create(lv_obj_0, 20, "Mix", &reverb_p0, "%d%%", 0, 100, REVERB);
        lv_obj_set_name(adjustment_20, "adjustment_20");

        lv_obj_t * adjustment_21 = adjustment_popup_create(lv_obj_0, 21, "Decay (0.1 s)", &reverb_p1, "%d", 1, 100, REVERB);
        lv_obj_set_name(adjustment_21, "adjustment_21");

        lv_obj_t * adjustment_22 = adjustment_popup_create(lv_obj_0, 22, "Damping", &reverb_p2, "%d%%", 0, 100, REVERB);
        lv_obj_set_name(adjustment_22, "adjustment_22");

        lv_obj_t * adjustment_100 = adjustment_popup_create(lv_obj_0, 100, "Master volume", &master, "%d%%", 0, 100, AMBER);
        lv_obj_set_name(adjustment_100, "adjustment_100");

        lv_obj_t * adjustment_101 = adjustment_popup_create(lv_obj_0, 101, "AUX volume", &aux, "%d%%", 0, 100, AMBER);
        lv_obj_set_name(adjustment_101, "adjustment_101");

        the_root = lv_obj_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

