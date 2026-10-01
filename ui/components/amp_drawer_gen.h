/**
 * @file amp_drawer_gen.h
 */

#ifndef LVGL_PRO_AMP_DRAWER_GEN_H
#define LVGL_PRO_AMP_DRAWER_GEN_H

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

typedef enum {
    AMP_DRAWER_TIMELINE_SLIDE = 0,
    _AMP_DRAWER_TIMELINE_CNT = 1
}amp_drawer_timeline_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

lv_obj_t * amp_drawer_create(lv_obj_t * parent);

/**
 * Get a timeline of a amp_drawer
 * @param obj          pointer to a amp_drawer component
 * @param timeline_id  ID of the the timeline
 * @return             pointer to the timeline or NULL if not found
 */
lv_anim_timeline_t * amp_drawer_get_timeline(lv_obj_t * obj, amp_drawer_timeline_t timeline_id);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LVGL_PRO_AMP_DRAWER_GEN_H*/