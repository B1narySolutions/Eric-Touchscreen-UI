#ifndef AMP_CHAIN_H
#define AMP_CHAIN_H

#include <stdint.h>
#if defined(__has_include) && __has_include("lvgl/lvgl.h")
#include "lvgl/lvgl.h"
#else
#include "lvgl.h"
#endif

#define AMP_CHAIN_BLOCK_COUNT 7

/* Called by each signal-block title. Block 7 (cabinet) is fixed and ignored. */
void amp_chain_drag_event(lv_event_t * event);
void amp_chain_lifecycle_event(lv_event_t * event);

/* Left-to-right block IDs: gate=0, comp=1, drive=2, amp=3,
 * chorus=4, delay=5, reverb=6. Cabinet/IR is always applied afterward and is
 * therefore intentionally absent from the reorderable array. */
void amp_chain_get_order(uint8_t out[AMP_CHAIN_BLOCK_COUNT]);

#endif
