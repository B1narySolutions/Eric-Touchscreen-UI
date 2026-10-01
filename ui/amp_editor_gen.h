/**
 * @file amp_editor_gen.h
 */

#ifndef LVGL_PRO_AMP_EDITOR_GEN_H
#define LVGL_PRO_AMP_EDITOR_GEN_H

#ifndef UI_SUBJECT_STRING_LENGTH
#define UI_SUBJECT_STRING_LENGTH 256
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
    #include "lvgl.h"
    #include "lvgl_private.h"
#else
    #include "lvgl/lvgl.h"
    #include "lvgl/lvgl_private.h"
#endif

#if defined(LV_USE_XML) && LV_USE_XML
    #include "lv_xml/lv_xml.h"
#endif



/* Prototypes for target functions, needed by responsive const definitions */

void amp_editor_set_target(uint32_t target);
uint32_t amp_editor_get_target(void);
bool amp_editor_check_target(uint32_t target);

/*********************
 *      DEFINES
 *********************/

#define AMP_EDITOR_TARGET_UNDEFINED  (0 << 1)
#define AMP_EDITOR_TARGET_TARGET1    (1 << 1)
#define AMP_EDITOR_TARGET_ALL        0x0FFFFFFF

/* By default compile for all targets, allowing to switch to any targets at runtime */
#ifndef AMP_EDITOR_COMPILE_TARGET
#define AMP_EDITOR_COMPILE_TARGET AMP_EDITOR_TARGET_ALL
#endif

#define AMP_EDITOR_CHECK_COMPILE_TARGET(target) (AMP_EDITOR_COMPILE_TARGET & (target) ? 1 : 0)

#define BACKGROUND lv_color_hex(0x111416)
#define PANEL lv_color_hex(0x1B2023)
#define EDGE lv_color_hex(0x343C40)
#define INK lv_color_hex(0xF2EEE6)
#define MUTED lv_color_hex(0xA0AAAE)
#define AMBER lv_color_hex(0xE9B76E)
#define BUTTON_BG lv_color_hex(0x282F33)
#define SELECTED_BG lv_color_hex(0x46392A)
#define GATE lv_color_hex(0x82B8AA)
#define COMP lv_color_hex(0xDFBE73)
#define DRIVE lv_color_hex(0xE7956B)
#define AMP lv_color_hex(0xE9B76E)
#define CHORUS lv_color_hex(0x86BCA9)
#define DELAY lv_color_hex(0x83AFDC)
#define REVERB lv_color_hex(0xB49DD5)
#define CABINET lv_color_hex(0xD39A72)


#ifndef LV_XML_EVAL_STRING_BUF_SIZE
    #define LV_XML_EVAL_STRING_BUF_SIZE 256
#endif

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL VARIABLES
 **********************/

/*-------------------
 * Permanent screens
 *------------------*/

/*----------------
 * Global styles
 *----------------*/

extern lv_style_t surface;
extern lv_style_t button_base;
extern lv_style_t button_pressed;

/*----------------
 * Fonts
 *----------------*/

/* Targets: any */
extern lv_font_t * font_14;
extern lv_font_t * font_16;
extern lv_font_t * font_24;
extern lv_font_t * font_28;
extern lv_font_t * font_20;
extern lv_font_t * font_48;


/*----------------
 * Images
 *----------------*/



/*----------------
 * Subjects
 *----------------*/

extern lv_subject_t selected_block;
extern lv_subject_t preset_number;
extern lv_subject_t voice;
extern lv_subject_t master;
extern lv_subject_t aux;
extern lv_subject_t muted_output;
extern lv_subject_t headphones;
extern lv_subject_t dialog;
extern lv_subject_t edited;
extern lv_subject_t gate_enabled;
extern lv_subject_t gate_p0;
extern lv_subject_t gate_p1;
extern lv_subject_t comp_enabled;
extern lv_subject_t comp_p0;
extern lv_subject_t comp_p1;
extern lv_subject_t comp_p2;
extern lv_subject_t drive_enabled;
extern lv_subject_t drive_p0;
extern lv_subject_t drive_p1;
extern lv_subject_t drive_p2;
extern lv_subject_t amp_enabled;
extern lv_subject_t amp_p0;
extern lv_subject_t amp_p1;
extern lv_subject_t amp_p2;
extern lv_subject_t amp_p3;
extern lv_subject_t amp_p4;
extern lv_subject_t chorus_enabled;
extern lv_subject_t chorus_p0;
extern lv_subject_t chorus_p1;
extern lv_subject_t chorus_p2;
extern lv_subject_t delay_enabled;
extern lv_subject_t delay_p0;
extern lv_subject_t delay_p1;
extern lv_subject_t delay_p2;
extern lv_subject_t reverb_enabled;
extern lv_subject_t reverb_p0;
extern lv_subject_t reverb_p1;
extern lv_subject_t reverb_p2;
extern lv_subject_t cabinet_enabled;
extern lv_subject_t cabinet_ir;
extern lv_subject_t sidebar_open;
extern lv_subject_t active_adjustment;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/*----------------
 * Event Callbacks
 *----------------*/

void amp_chain_drag_event(lv_event_t * e);
void amp_chain_lifecycle_event(lv_event_t * e);

/**
 * Initialize the component library
 */

void amp_editor_init_gen(const char * asset_path);

/**********************
 *      MACROS
 **********************/

/**********************
 *   POST INCLUDES
 **********************/

/*Include all the widgets, components and screens of this library*/
#include "components/adjustment_popup_gen.h"
#include "components/amp_button_gen.h"
#include "components/amp_drawer_gen.h"
#include "components/amp_panel_gen.h"
#include "components/cabinet_panel_gen.h"
#include "components/amplifier_selector_gen.h"
#include "components/chorus_panel_gen.h"
#include "components/comp_panel_gen.h"
#include "components/delay_panel_gen.h"
#include "components/drive_panel_gen.h"
#include "components/gate_panel_gen.h"
#include "components/parameter_dial_gen.h"
#include "components/preview_dialogs_gen.h"
#include "components/reverb_panel_gen.h"
#include "components/signal_block_gen.h"
#include "screens/home_gen.h"

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LVGL_PRO_AMP_EDITOR_GEN_H*/
