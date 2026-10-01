#include "amp_chain.h"

#include <stdbool.h>

#define SLOT_WIDTH 123
#define BLOCK_WIDTH 113
#define LAST_SLOT_X (SLOT_WIDTH * (AMP_CHAIN_BLOCK_COUNT - 1))
#define DRAG_THRESHOLD 10

static lv_obj_t * chain;
static lv_obj_t * blocks_by_id[AMP_CHAIN_BLOCK_COUNT];
static lv_obj_t * blocks_in_slot[AMP_CHAIN_BLOCK_COUNT];
static uint8_t block_order[AMP_CHAIN_BLOCK_COUNT] = { 0, 1, 2, 3, 4, 5, 6 };

static struct {
    lv_obj_t * block;
    lv_point_t press_point;
    int32_t press_x;
    int32_t start_slot;
    int32_t current_slot;
    bool moved;
} drag;

static int32_t right_limit(void)
{
    if(chain == NULL) return LAST_SLOT_X;

    int32_t available = lv_obj_get_content_width(chain) - BLOCK_WIDTH;
    if(available < 0) return 0;
    return available < LAST_SLOT_X ? available : LAST_SLOT_X;
}

static int32_t clamp_x(int32_t x)
{
    if(x < 0) return 0;
    int32_t limit = right_limit();
    if(x > limit) return limit;
    return x;
}

static void snap_to_slot(lv_obj_t * block, int32_t slot)
{
    lv_obj_set_x(block, clamp_x(slot * SLOT_WIDTH));
}

static void normalize_block_geometry(lv_obj_t * block)
{
    /* Keep old generated component files from restoring the former 132 px size. */
    lv_obj_set_width(block, BLOCK_WIDTH);
    uint32_t child_count = lv_obj_get_child_count(block);
    for(uint32_t i = 0; i < child_count; i++) {
        lv_obj_set_width(lv_obj_get_child(block, i), BLOCK_WIDTH);
    }
}

static void capture_chain(lv_obj_t * parent)
{
    if(chain == parent || lv_obj_get_child_count(parent) != AMP_CHAIN_BLOCK_COUNT) return;

    chain = parent;
    lv_obj_set_width(chain, LAST_SLOT_X + BLOCK_WIDTH);
    lv_obj_remove_flag(chain, LV_OBJ_FLAG_OVERFLOW_VISIBLE);
    for(int32_t i = 0; i < AMP_CHAIN_BLOCK_COUNT; i++) {
        lv_obj_t * block = lv_obj_get_child(chain, i);
        normalize_block_geometry(block);
        snap_to_slot(block, i);
        blocks_by_id[i] = block;
        blocks_in_slot[i] = block;
        block_order[i] = (uint8_t)i;
    }
    drag.block = NULL;
}

void amp_chain_lifecycle_event(lv_event_t * event)
{
    lv_event_code_t code = lv_event_get_code(event);
    /* Initialize on the first press, after XML construction and layout finish. */
    if(code == LV_EVENT_DELETE) {
        chain = NULL;
        drag.block = NULL;
        for(int32_t i = 0; i < AMP_CHAIN_BLOCK_COUNT; i++) {
            blocks_by_id[i] = NULL;
            blocks_in_slot[i] = NULL;
            block_order[i] = (uint8_t)i;
        }
    }
}

static int32_t find_slot(lv_obj_t * block)
{
    for(int32_t i = 0; i < AMP_CHAIN_BLOCK_COUNT; i++) {
        if(blocks_in_slot[i] == block) return i;
    }
    return -1;
}

static void move_into_slot(int32_t target)
{
    int32_t old = drag.current_slot;
    if(target == old) return;

    lv_obj_t * moving = blocks_in_slot[old];
    if(target > old) {
        for(int32_t i = old; i < target; i++) {
            blocks_in_slot[i] = blocks_in_slot[i + 1];
            snap_to_slot(blocks_in_slot[i], i);
        }
    }
    else {
        for(int32_t i = old; i > target; i--) {
            blocks_in_slot[i] = blocks_in_slot[i - 1];
            snap_to_slot(blocks_in_slot[i], i);
        }
    }
    blocks_in_slot[target] = moving;
    drag.current_slot = target;
}

static void finish_drag(void)
{
    if(drag.block == NULL) return;

    if(drag.moved) {
        snap_to_slot(drag.block, drag.current_slot);
        lv_obj_set_style_translate_y(drag.block, 0, 0);
        /* Restore child order to the visible slot order after raising while dragging. */
        for(int32_t slot = 0; slot < AMP_CHAIN_BLOCK_COUNT; slot++) {
            lv_obj_move_to_index(blocks_in_slot[slot], slot);
        }
        lv_obj_update_layout(chain);

        if(drag.current_slot != drag.start_slot) {
            for(int32_t slot = 0; slot < AMP_CHAIN_BLOCK_COUNT; slot++) {
                for(int32_t id = 0; id < AMP_CHAIN_BLOCK_COUNT; id++) {
                    if(blocks_in_slot[slot] == blocks_by_id[id]) {
                        block_order[slot] = (uint8_t)id;
                        break;
                    }
                }
            }
            /* The XML uses this event to mark the preset as edited. */
            lv_obj_send_event(chain, LV_EVENT_VALUE_CHANGED, NULL);
        }
    }
    drag.block = NULL;
}

void amp_chain_drag_event(lv_event_t * event)
{
    lv_event_code_t code = lv_event_get_code(event);
    if(code != LV_EVENT_PRESSED && code != LV_EVENT_PRESSING &&
       code != LV_EVENT_RELEASED && code != LV_EVENT_PRESS_LOST) return;

    lv_obj_t * button = lv_event_get_current_target(event);
    lv_obj_t * block = lv_obj_get_parent(button);
    lv_obj_t * parent = lv_obj_get_parent(block);
    lv_indev_t * indev = lv_event_get_indev(event);

    if(code == LV_EVENT_PRESSED) {
        capture_chain(parent);
        if(chain != parent || indev == NULL) return;
        drag.block = block;
        drag.start_slot = find_slot(block);
        if(drag.start_slot < 0) {
            drag.block = NULL;
            return;
        }
        drag.current_slot = drag.start_slot;
        drag.press_x = lv_obj_get_x(block);
        drag.moved = false;
        lv_indev_get_point(indev, &drag.press_point);
        return;
    }

    if(drag.block != block) return;
    if(code == LV_EVENT_RELEASED || code == LV_EVENT_PRESS_LOST) {
        finish_drag();
        return;
    }
    if(indev == NULL) return;

    lv_point_t point;
    lv_indev_get_point(indev, &point);
    int32_t dx = point.x - drag.press_point.x;
    if(!drag.moved && dx > -DRAG_THRESHOLD && dx < DRAG_THRESHOLD) return;

    if(!drag.moved) {
        drag.moved = true;
        lv_obj_move_to_index(block, -1);
        lv_obj_set_style_translate_y(block, -6, 0);
    }
    int32_t x = clamp_x(drag.press_x + dx);
    lv_obj_set_x(block, x);

    int32_t target = (x + SLOT_WIDTH / 2) / SLOT_WIDTH;
    if(target != drag.current_slot) move_into_slot(target);
    lv_obj_update_layout(chain);
}

void amp_chain_get_order(uint8_t out[AMP_CHAIN_BLOCK_COUNT])
{
    if(out == NULL) return;
    for(int32_t i = 0; i < AMP_CHAIN_BLOCK_COUNT; i++) out[i] = block_order[i];
}
