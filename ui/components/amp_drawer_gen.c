/**
 * @file amp_drawer_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "amp_drawer_gen.h"
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

static lv_anim_timeline_t * timeline_slide_create(lv_obj_t * obj);
static void free_timeline_event_cb(lv_event_t * e);

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t * amp_drawer_create(lv_obj_t * parent)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if AMP_EDITOR_CHECK_COMPILE_TARGET(AMP_EDITOR_TARGET_ALL)
    if (amp_editor_check_target(AMP_EDITOR_TARGET_ALL)) {
        lv_obj_t * lv_obj_0 = lv_obj_create(parent);
        lv_obj_set_name_static(lv_obj_0, "amp_drawer_#");
        lv_obj_set_style_bg_opa(lv_obj_0, (255 * 0 / 100), 0);
        lv_obj_set_style_border_width(lv_obj_0, 0, 0);
        lv_obj_set_style_pad_all(lv_obj_0, 0, 0);
        lv_obj_set_style_radius(lv_obj_0, 0, 0);
        lv_obj_set_flag(lv_obj_0, LV_OBJ_FLAG_SCROLLABLE, false);
        lv_obj_set_width(lv_obj_0, 1024);
        lv_obj_set_height(lv_obj_0, 600);
        lv_obj_set_flag(lv_obj_0, LV_OBJ_FLAG_CLICKABLE, false);

        lv_obj_t * model_trigger = amp_button_create(lv_obj_0, "");
        lv_obj_set_name(model_trigger, "model_trigger");
        lv_obj_set_x(model_trigger, 204);
        lv_obj_set_y(model_trigger, 16);
        lv_obj_set_width(model_trigger, 432);
        lv_obj_set_height(model_trigger, 64);
        lv_obj_set_style_bg_color(model_trigger, lv_color_hex(0x202628), 0);
        lv_obj_set_style_border_color(model_trigger, EDGE, 0);
        lv_obj_t * lv_label_0 = lv_label_create(model_trigger);
        lv_label_set_text(lv_label_0, "AMP MODEL");
        lv_obj_set_x(lv_label_0, 16);
        lv_obj_set_y(lv_label_0, 7);
        lv_obj_set_style_text_font(lv_label_0, font_14, 0);
        lv_obj_set_style_text_color(lv_label_0, MUTED, 0);

        lv_obj_t * lv_label_1 = lv_label_create(model_trigger);
        lv_label_set_text(lv_label_1, "Fender '65 Twin Reverb");
        lv_obj_set_x(lv_label_1, 16);
        lv_obj_set_y(lv_label_1, 30);
        lv_obj_set_style_text_font(lv_label_1, font_20, 0);
        lv_obj_set_style_text_color(lv_label_1, AMBER, 0);
        lv_obj_bind_flag_if_not_eq(lv_label_1, &voice, LV_OBJ_FLAG_HIDDEN, 0);

        lv_obj_t * lv_label_2 = lv_label_create(model_trigger);
        lv_label_set_text(lv_label_2, "Vox AC30");
        lv_obj_set_x(lv_label_2, 16);
        lv_obj_set_y(lv_label_2, 30);
        lv_obj_set_style_text_font(lv_label_2, font_20, 0);
        lv_obj_set_style_text_color(lv_label_2, AMBER, 0);
        lv_obj_bind_flag_if_not_eq(lv_label_2, &voice, LV_OBJ_FLAG_HIDDEN, 1);

        lv_obj_t * lv_label_3 = lv_label_create(model_trigger);
        lv_label_set_text(lv_label_3, "Marshall JCM800");
        lv_obj_set_x(lv_label_3, 16);
        lv_obj_set_y(lv_label_3, 30);
        lv_obj_set_style_text_font(lv_label_3, font_20, 0);
        lv_obj_set_style_text_color(lv_label_3, AMBER, 0);
        lv_obj_bind_flag_if_not_eq(lv_label_3, &voice, LV_OBJ_FLAG_HIDDEN, 2);

        lv_obj_t * lv_label_4 = lv_label_create(model_trigger);
        lv_label_set_text(lv_label_4, "v");
        lv_obj_set_align(lv_label_4, LV_ALIGN_RIGHT_MID);
        lv_obj_set_x(lv_label_4, -18);
        lv_obj_set_style_text_font(lv_label_4, font_24, 0);
        lv_obj_set_style_text_color(lv_label_4, AMBER, 0);

        lv_obj_add_subject_set_int_event(model_trigger, &sidebar_open, LV_EVENT_CLICKED, 1);

        lv_obj_t * dismiss_area = lv_obj_create(lv_obj_0);
        lv_obj_set_style_bg_opa(dismiss_area, (255 * 24 / 100), 0);
        lv_obj_set_style_border_width(dismiss_area, 0, 0);
        lv_obj_set_style_pad_all(dismiss_area, 0, 0);
        lv_obj_set_style_radius(dismiss_area, 0, 0);
        lv_obj_set_flag(dismiss_area, LV_OBJ_FLAG_SCROLLABLE, false);
        lv_obj_set_name(dismiss_area, "dismiss_area");
        lv_obj_set_width(dismiss_area, 1024);
        lv_obj_set_height(dismiss_area, 600);
        lv_obj_set_flag(dismiss_area, LV_OBJ_FLAG_CLICKABLE, true);
        lv_obj_set_flag(dismiss_area, LV_OBJ_FLAG_GESTURE_BUBBLE, false);
        lv_obj_set_style_bg_color(dismiss_area, BACKGROUND, 0);
        lv_obj_bind_flag_if_not_eq(dismiss_area, &sidebar_open, LV_OBJ_FLAG_HIDDEN, 1);
        lv_obj_add_subject_set_int_event(dismiss_area, &sidebar_open, LV_EVENT_CLICKED, 0);
        lv_obj_add_subject_set_int_event(dismiss_area, &sidebar_open, LV_EVENT_GESTURE, 0);

        lv_obj_t * drawer = amplifier_selector_create(lv_obj_0);
        lv_obj_set_name(drawer, "drawer");
        lv_obj_set_x(drawer, 210);
        lv_obj_set_y(drawer, 88);
        lv_obj_set_style_translate_y(drawer, -400, 0);
        lv_obj_set_flag(drawer, LV_OBJ_FLAG_GESTURE_BUBBLE, false);
        lv_obj_add_subject_set_int_event(drawer, &sidebar_open, LV_EVENT_GESTURE, 0);
        lv_obj_t * amp_button_0 = amp_button_create(drawer, "X");
        lv_obj_set_x(amp_button_0, 364);
        lv_obj_set_y(amp_button_0, 2);
        lv_obj_set_width(amp_button_0, 44);
        lv_obj_set_height(amp_button_0, 42);
        lv_obj_set_style_bg_opa(amp_button_0, (255 * 0 / 100), 0);
        lv_obj_set_style_border_width(amp_button_0, 0, 0);
        lv_obj_add_subject_set_int_event(amp_button_0, &sidebar_open, LV_EVENT_CLICKED, 0);


        /* create animation timeline(s) */
        lv_anim_timeline_t ** at_array = lv_malloc(sizeof(lv_anim_timeline_t *) * _AMP_DRAWER_TIMELINE_CNT);
        at_array[AMP_DRAWER_TIMELINE_SLIDE] = timeline_slide_create(lv_obj_0);
        lv_obj_set_user_data(lv_obj_0, at_array);
        lv_obj_add_event_cb(lv_obj_0, free_timeline_event_cb, LV_EVENT_DELETE, at_array);

        lv_obj_add_play_timeline_event(model_trigger, LV_EVENT_CLICKED, amp_drawer_get_timeline(lv_obj_0, AMP_DRAWER_TIMELINE_SLIDE), 0, false);
        lv_obj_add_play_timeline_event(dismiss_area, LV_EVENT_CLICKED, amp_drawer_get_timeline(lv_obj_0, AMP_DRAWER_TIMELINE_SLIDE), 0, true);
        lv_obj_add_play_timeline_event(dismiss_area, LV_EVENT_GESTURE, amp_drawer_get_timeline(lv_obj_0, AMP_DRAWER_TIMELINE_SLIDE), 0, true);
        lv_obj_add_play_timeline_event(drawer, LV_EVENT_GESTURE, amp_drawer_get_timeline(lv_obj_0, AMP_DRAWER_TIMELINE_SLIDE), 0, true);
        lv_obj_add_play_timeline_event(amp_button_0, LV_EVENT_CLICKED, amp_drawer_get_timeline(lv_obj_0, AMP_DRAWER_TIMELINE_SLIDE), 0, true);

        the_root = lv_obj_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

lv_anim_timeline_t * amp_drawer_get_timeline(lv_obj_t * obj, amp_drawer_timeline_t timeline_id)
{
    if (timeline_id >= _AMP_DRAWER_TIMELINE_CNT) {
        LV_LOG_WARN("amp_drawer has no timeline with %d ID", timeline_id);
        return NULL;
    }

    lv_anim_timeline_t ** at_array = lv_obj_get_user_data(obj);
    return at_array[timeline_id];
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/* Helper function to execute animations */
static void int_anim_exec_cb(lv_anim_t * a, int32_t v)
{
    uint32_t data = (lv_uintptr_t)lv_anim_get_user_data(a);
    lv_style_prop_t prop = data >> 24;
    lv_style_selector_t selector = data & 0x00ffffff;

    lv_style_value_t style_value;
    style_value.num = v;
    lv_obj_set_local_style_prop(a->var, prop, style_value, selector);
}

static lv_anim_timeline_t * timeline_slide_create(lv_obj_t * obj)
{
    lv_anim_timeline_t * at = lv_anim_timeline_create();
    lv_anim_timeline_t * at_to_merge = NULL;

    lv_anim_t a;
    uint32_t selector_and_prop;

    selector_and_prop = ((LV_STYLE_TRANSLATE_Y & 0xff) << 24) | 0;
    lv_anim_init(&a);
    lv_anim_set_custom_exec_cb(&a, int_anim_exec_cb);
    lv_anim_set_var(&a, lv_obj_find_by_name(obj, "drawer"));
    lv_anim_set_values(&a, -400, 0);
    lv_anim_set_duration(&a, 120);
    lv_anim_set_user_data(&a, (void *)((uintptr_t)selector_and_prop));
    lv_anim_timeline_add(at, 0, &a);

    return at;
}

static void free_timeline_event_cb(lv_event_t * e)
{
    lv_anim_timeline_t ** at_array = lv_event_get_user_data(e);
    uint32_t i;
    for(i = 0; i < _AMP_DRAWER_TIMELINE_CNT; i++) {
        lv_anim_timeline_delete(at_array[i]);
    }
    lv_free(at_array);
}

