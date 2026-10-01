/**
 * @file parameter_dial_gen.h
 */

#ifndef LVGL_PRO_PARAMETER_DIAL_GEN_H
#define LVGL_PRO_PARAMETER_DIAL_GEN_H

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

lv_obj_t * parameter_dial_create(lv_obj_t * parent, const char * title, lv_subject_t * subject, const char * format, int32_t minimum, int32_t maximum, int32_t step, int32_t negative_step, lv_color_t accent, int32_t control_id);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LVGL_PRO_PARAMETER_DIAL_GEN_H*/