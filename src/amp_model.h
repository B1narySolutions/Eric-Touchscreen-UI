#ifndef AMP_MODEL_H
#define AMP_MODEL_H
#include <stdbool.h>

enum { AMP_GATE, AMP_COMP, AMP_DRIVE, AMP_AMP, AMP_CHORUS, AMP_DELAY, AMP_REVERB, AMP_BLOCK_COUNT };
typedef struct { int voice; int value[AMP_BLOCK_COUNT][5]; bool enabled[AMP_BLOCK_COUNT]; } amp_tone_t;
typedef struct { const char *name; const char *unit; int min, max, step; } amp_parameter_t;
typedef struct { const char *name; const char *description; unsigned color; int count; amp_parameter_t parameters[5]; } amp_block_t;
extern const amp_block_t amp_blocks[AMP_BLOCK_COUNT];
extern const char *amp_voices[3];
extern const char *amp_voice_details[3];
extern const char *amp_preset_names[3];
void amp_factory_tone(int preset, amp_tone_t *tone);
bool amp_tone_equal(const amp_tone_t *a, const amp_tone_t *b);
#endif
