/**
 * @file adjustment_popup_gen.h
 */

#ifndef LVGL_PRO_ADJUSTMENT_POPUP_GEN_H
#define LVGL_PRO_ADJUSTMENT_POPUP_GEN_H

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

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

lv_obj_t * adjustment_popup_create(lv_obj_t * parent, int32_t control_id, const char * title, lv_subject_t * subject, const char * format, int32_t minimum, int32_t maximum, lv_color_t accent);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LVGL_PRO_ADJUSTMENT_POPUP_GEN_H*/