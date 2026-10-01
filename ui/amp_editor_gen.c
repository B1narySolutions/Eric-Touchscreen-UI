/**
 * @file amp_editor_gen.c
 */

/*********************
 *      INCLUDES
 *********************/

#include "amp_editor_gen.h"

#if defined(LV_USE_XML) && LV_USE_XML
#endif /* LV_USE_XML */

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void check_font(lv_font_t ** font, const char * name);

/**********************
 *  STATIC VARIABLES
 **********************/

static uint32_t amp_editor_target = AMP_EDITOR_TARGET_ALL;

/*----------------
 * Translations
 *----------------*/

#ifndef LV_EDITOR_PREVIEW
    static const char * translation_languages[] = {"en", "de", NULL};
    static const char * translation_tags[] = {"dog", "cat", "house", NULL};
    static const char * translation_texts[] = {
        "This is a dog", "Das ist ein Hund", /* dog */
        "A curious little cat", "Eine neugierige kleine Katze", /* cat */
        "The house is cozy and warm", "Das Haus ist gemütlich und warm", /* house */
    };
#endif

/**********************
 *  GLOBAL VARIABLES
 **********************/

/*--------------------
 *  Permanent screens
 *-------------------*/

/*----------------
 * Fonts
 *----------------*/

lv_font_t * font_14;
lv_font_t * font_16;
lv_font_t * font_24;
lv_font_t * font_28;
lv_font_t * font_20;
lv_font_t * font_48;

/*----------------
 * Images
 *----------------*/



/*----------------
 * Global styles
 *----------------*/

lv_style_t surface;
lv_style_t button_base;
lv_style_t button_pressed;

/*----------------
 * Subjects
 *----------------*/

lv_subject_t selected_block;
lv_subject_t preset_number;
lv_subject_t voice;
lv_subject_t master;
lv_subject_t aux;
lv_subject_t muted_output;
lv_subject_t headphones;
lv_subject_t dialog;
lv_subject_t edited;
lv_subject_t gate_enabled;
lv_subject_t gate_p0;
lv_subject_t gate_p1;
lv_subject_t comp_enabled;
lv_subject_t comp_p0;
lv_subject_t comp_p1;
lv_subject_t comp_p2;
lv_subject_t drive_enabled;
lv_subject_t drive_p0;
lv_subject_t drive_p1;
lv_subject_t drive_p2;
lv_subject_t amp_enabled;
lv_subject_t amp_p0;
lv_subject_t amp_p1;
lv_subject_t amp_p2;
lv_subject_t amp_p3;
lv_subject_t amp_p4;
lv_subject_t chorus_enabled;
lv_subject_t chorus_p0;
lv_subject_t chorus_p1;
lv_subject_t chorus_p2;
lv_subject_t delay_enabled;
lv_subject_t delay_p0;
lv_subject_t delay_p1;
lv_subject_t delay_p2;
lv_subject_t reverb_enabled;
lv_subject_t reverb_p0;
lv_subject_t reverb_p1;
lv_subject_t reverb_p2;
lv_subject_t cabinet_enabled;
lv_subject_t cabinet_ir;
lv_subject_t sidebar_open;
lv_subject_t active_adjustment;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void amp_editor_init_gen(const char * asset_path)
{
    char buf[256];


    /*----------------
     * Fonts
     *----------------*/

    /* Targets: any */

    #if AMP_EDITOR_CHECK_COMPILE_TARGET(AMP_EDITOR_TARGET_ALL)
    if (amp_editor_check_target(AMP_EDITOR_TARGET_ALL)) {
        if (!font_14) {
            /* font_14 */
            /* create tiny ttf font "font_14" from file */
            lv_snprintf(buf, 256, "%s%s", asset_path, "fonts/Montserrat_Medium.ttf");
            font_14 = lv_tiny_ttf_create_file(buf, 14);
        }
        if (!font_16) {
            /* font_16 */
            /* create tiny ttf font "font_16" from file */
            lv_snprintf(buf, 256, "%s%s", asset_path, "fonts/Montserrat_Medium.ttf");
            font_16 = lv_tiny_ttf_create_file(buf, 16);
        }
        if (!font_24) {
            /* font_24 */
            /* create tiny ttf font "font_24" from file */
            lv_snprintf(buf, 256, "%s%s", asset_path, "fonts/Montserrat_Medium.ttf");
            font_24 = lv_tiny_ttf_create_file(buf, 24);
        }
        if (!font_28) {
            /* font_28 */
            /* create tiny ttf font "font_28" from file */
            lv_snprintf(buf, 256, "%s%s", asset_path, "fonts/Montserrat_Medium.ttf");
            font_28 = lv_tiny_ttf_create_file(buf, 28);
        }
        if (!font_20) {
            /* font_20 */
            /* create tiny ttf font "font_20" from file */
            lv_snprintf(buf, 256, "%s%s", asset_path, "fonts/Montserrat_Medium.ttf");
            font_20 = lv_tiny_ttf_create_file(buf, 20);
        }
        if (!font_48) {
            /* font_48 */
            /* create tiny ttf font "font_48" from file */
            lv_snprintf(buf, 256, "%s%s", asset_path, "fonts/Montserrat_Medium.ttf");
            font_48 = lv_tiny_ttf_create_file(buf, 48);
        }
    }
    #endif

    /*----------------
     * Images
     *----------------*/



    /*----------------
     * Global styles
     *----------------*/

    static bool style_inited = false;

    if (!style_inited) {
        /*Init all styles*/
        lv_style_init(&surface);
        lv_style_init(&button_base);
        lv_style_init(&button_pressed);

        lv_style_set_bg_color(&surface, PANEL);
        lv_style_set_bg_opa(&surface, (255 * 100 / 100));
        lv_style_set_border_width(&surface, 0);
        lv_style_set_pad_all(&surface, 0);
        lv_style_set_radius(&surface, 16);
        lv_style_set_text_color(&surface, INK);
        lv_style_set_text_font(&surface, font_16);
        lv_style_set_bg_color(&button_base, BUTTON_BG);
        lv_style_set_bg_opa(&button_base, (255 * 100 / 100));
        lv_style_set_border_width(&button_base, 1);
        lv_style_set_border_color(&button_base, EDGE);
        lv_style_set_pad_all(&button_base, 0);
        lv_style_set_radius(&button_base, 10);
        lv_style_set_text_color(&button_base, INK);
        lv_style_set_text_font(&button_base, font_16);
        lv_style_set_shadow_width(&button_base, 0);
        lv_style_set_bg_color(&button_pressed, lv_color_hex(0x434B50));

        style_inited = true;
    }

    /*----------------
     * Subjects
     *----------------*/
    lv_subject_init_int(&selected_block, 3);
    lv_subject_init_int(&preset_number, 1);
    lv_subject_init_int(&voice, 0);
    lv_subject_init_int(&master, 65);
    lv_subject_init_int(&aux, 35);
    lv_subject_init_int(&muted_output, 0);
    lv_subject_init_int(&headphones, 0);
    lv_subject_init_int(&dialog, 0);
    lv_subject_init_int(&edited, 0);
    lv_subject_init_int(&gate_enabled, 0);
    lv_subject_init_int(&gate_p0, -55);
    lv_subject_init_int(&gate_p1, 120);
    lv_subject_init_int(&comp_enabled, 0);
    lv_subject_init_int(&comp_p0, 65);
    lv_subject_init_int(&comp_p1, 20);
    lv_subject_init_int(&comp_p2, 40);
    lv_subject_init_int(&drive_enabled, 0);
    lv_subject_init_int(&drive_p0, 55);
    lv_subject_init_int(&drive_p1, 35);
    lv_subject_init_int(&drive_p2, 55);
    lv_subject_init_int(&amp_enabled, 1);
    lv_subject_init_int(&amp_p0, 32);
    lv_subject_init_int(&amp_p1, 50);
    lv_subject_init_int(&amp_p2, 45);
    lv_subject_init_int(&amp_p3, 62);
    lv_subject_init_int(&amp_p4, 65);
    lv_subject_init_int(&chorus_enabled, 0);
    lv_subject_init_int(&chorus_p0, 25);
    lv_subject_init_int(&chorus_p1, 12);
    lv_subject_init_int(&chorus_p2, 40);
    lv_subject_init_int(&delay_enabled, 0);
    lv_subject_init_int(&delay_p0, 22);
    lv_subject_init_int(&delay_p1, 380);
    lv_subject_init_int(&delay_p2, 30);
    lv_subject_init_int(&reverb_enabled, 1);
    lv_subject_init_int(&reverb_p0, 28);
    lv_subject_init_int(&reverb_p1, 24);
    lv_subject_init_int(&reverb_p2, 45);
    lv_subject_init_int(&cabinet_enabled, 1);
    lv_subject_init_int(&cabinet_ir, 0);
    lv_subject_init_int(&sidebar_open, 0);
    lv_subject_init_int(&active_adjustment, 0);

    /*----------------
     * Translations
     *----------------*/

    #ifndef LV_EDITOR_PREVIEW
        lv_translation_add_static(translation_languages, translation_tags, translation_texts);
        lv_translation_set_language(translation_languages[0]);
    #endif

#if defined(LV_USE_XML) && LV_USE_XML
    /* Register widgets */

    /* Check all fonts / default if needed. This prevents fonts that are used in one target but
       defined in another from causing assertion failures during rendering of the Preview. */
    check_font(&font_14, "font_14");
    check_font(&font_16, "font_16");
    check_font(&font_24, "font_24");
    check_font(&font_28, "font_28");
    check_font(&font_20, "font_20");
    check_font(&font_48, "font_48");

    /* Register fonts */
    lv_xml_register_font(NULL, "font_14", font_14);
    lv_xml_register_font(NULL, "font_16", font_16);
    lv_xml_register_font(NULL, "font_24", font_24);
    lv_xml_register_font(NULL, "font_28", font_28);
    lv_xml_register_font(NULL, "font_20", font_20);
    lv_xml_register_font(NULL, "font_48", font_48);

    /* Register subjects */
    lv_xml_register_subject(NULL, "selected_block", &selected_block);
    lv_xml_register_subject(NULL, "preset_number", &preset_number);
    lv_xml_register_subject(NULL, "voice", &voice);
    lv_xml_register_subject(NULL, "master", &master);
    lv_xml_register_subject(NULL, "aux", &aux);
    lv_xml_register_subject(NULL, "muted_output", &muted_output);
    lv_xml_register_subject(NULL, "headphones", &headphones);
    lv_xml_register_subject(NULL, "dialog", &dialog);
    lv_xml_register_subject(NULL, "edited", &edited);
    lv_xml_register_subject(NULL, "gate_enabled", &gate_enabled);
    lv_xml_register_subject(NULL, "gate_p0", &gate_p0);
    lv_xml_register_subject(NULL, "gate_p1", &gate_p1);
    lv_xml_register_subject(NULL, "comp_enabled", &comp_enabled);
    lv_xml_register_subject(NULL, "comp_p0", &comp_p0);
    lv_xml_register_subject(NULL, "comp_p1", &comp_p1);
    lv_xml_register_subject(NULL, "comp_p2", &comp_p2);
    lv_xml_register_subject(NULL, "drive_enabled", &drive_enabled);
    lv_xml_register_subject(NULL, "drive_p0", &drive_p0);
    lv_xml_register_subject(NULL, "drive_p1", &drive_p1);
    lv_xml_register_subject(NULL, "drive_p2", &drive_p2);
    lv_xml_register_subject(NULL, "amp_enabled", &amp_enabled);
    lv_xml_register_subject(NULL, "amp_p0", &amp_p0);
    lv_xml_register_subject(NULL, "amp_p1", &amp_p1);
    lv_xml_register_subject(NULL, "amp_p2", &amp_p2);
    lv_xml_register_subject(NULL, "amp_p3", &amp_p3);
    lv_xml_register_subject(NULL, "amp_p4", &amp_p4);
    lv_xml_register_subject(NULL, "chorus_enabled", &chorus_enabled);
    lv_xml_register_subject(NULL, "chorus_p0", &chorus_p0);
    lv_xml_register_subject(NULL, "chorus_p1", &chorus_p1);
    lv_xml_register_subject(NULL, "chorus_p2", &chorus_p2);
    lv_xml_register_subject(NULL, "delay_enabled", &delay_enabled);
    lv_xml_register_subject(NULL, "delay_p0", &delay_p0);
    lv_xml_register_subject(NULL, "delay_p1", &delay_p1);
    lv_xml_register_subject(NULL, "delay_p2", &delay_p2);
    lv_xml_register_subject(NULL, "reverb_enabled", &reverb_enabled);
    lv_xml_register_subject(NULL, "reverb_p0", &reverb_p0);
    lv_xml_register_subject(NULL, "reverb_p1", &reverb_p1);
    lv_xml_register_subject(NULL, "reverb_p2", &reverb_p2);
    lv_xml_register_subject(NULL, "cabinet_enabled", &cabinet_enabled);
    lv_xml_register_subject(NULL, "cabinet_ir", &cabinet_ir);
    lv_xml_register_subject(NULL, "sidebar_open", &sidebar_open);
    lv_xml_register_subject(NULL, "active_adjustment", &active_adjustment);

    /* Register callbacks */
    lv_xml_register_event_cb(NULL, "amp_chain_drag_event", amp_chain_drag_event);
    lv_xml_register_event_cb(NULL, "amp_chain_lifecycle_event", amp_chain_lifecycle_event);
#endif

    /* Register all the global assets so that they won't be created again when globals.xml is parsed.
     * While running in the editor skip this step to update the preview when the XML changes */
#if defined(LV_USE_XML) && LV_USE_XML && !defined(LV_EDITOR_PREVIEW)
    /* Register images */
#endif

#if !defined(LV_USE_XML) || LV_USE_XML == 0
    /*--------------------
     *  Permanent screens
     *-------------------*/
    /* If XML is enabled it's assumed that the permanent screens are created
     * manually from XML using lv_xml_create() */
#endif
}

void amp_editor_set_target(uint32_t target)
{
    amp_editor_target = target;
}

uint32_t amp_editor_get_target(void)
{
    return amp_editor_target;
}

bool amp_editor_check_target(uint32_t target)
{
    return (amp_editor_target & target) ? true : false;
}

/* Callbacks */
#if defined(LV_EDITOR_PREVIEW)
void __attribute__((weak)) amp_chain_drag_event(lv_event_t * e)
{
    LV_UNUSED(e);
    LV_LOG("amp_chain_drag_event was called\n");
}
void __attribute__((weak)) amp_chain_lifecycle_event(lv_event_t * e)
{
    LV_UNUSED(e);
    LV_LOG("amp_chain_lifecycle_event was called\n");
}
#endif

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void check_font(lv_font_t ** font, const char * name)
{
    if (!(*font)) {
        *font = (lv_font_t *)LV_FONT_DEFAULT;
        LV_LOG_WARN("font `%s` was not set. Using `LV_FONT_DEFAULT` instead", name);
    }
}
