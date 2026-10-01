/**
 * @file amp_editor.c
 */

/*********************
 *      INCLUDES
 *********************/

#include "amp_editor.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void amp_editor_init(const char * asset_path)
{
    LV_LOG("Initializing custom C code using LVGL v%d.%d.%d", LVGL_VERSION_MAJOR, LVGL_VERSION_MINOR, LVGL_VERSION_PATCH);

#ifdef ESP_PLATFORM
    /*
     * The desktop/editor build loads Montserrat from the project TTF file.
     * On the ESP32 use compiled fonts so UI creation cannot receive a NULL
     * font when the SPIFFS-backed TTF loader is unavailable or runs out of
     * file handles during startup.
     */
    font_14 = (lv_font_t *)&lv_font_montserrat_14;
    font_16 = (lv_font_t *)&lv_font_montserrat_16;
    font_20 = (lv_font_t *)&lv_font_montserrat_20;
    font_24 = (lv_font_t *)&lv_font_montserrat_24;
    font_28 = (lv_font_t *)&lv_font_montserrat_28;
    font_48 = (lv_font_t *)&lv_font_montserrat_48;
#endif

    amp_editor_init_gen(asset_path);

    /* Add your own custom code here if needed */
}

/**********************
 *   STATIC FUNCTIONS
 **********************/