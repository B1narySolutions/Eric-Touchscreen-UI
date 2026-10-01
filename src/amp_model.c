#include "amp_model.h"
#include <string.h>
/* Prototype ranges only. Confirm these with the audio/DSP implementation. */
const amp_block_t amp_blocks[AMP_BLOCK_COUNT] = {
    {"GATE", "Keep the quiet parts quiet.", 0x82B8AA, 2, {{"Threshold", " dB", -80, 0, 1}, {"Release", " ms", 10, 500, 10}}},
    {"COMP", "Even dynamics. Longer sustain.", 0xDFBE73, 3, {{"Level", "%", 0, 100, 1}, {"Attack", " ms", 1, 100, 1}, {"Sustain", "%", 0, 100, 1}}},
    {"DRIVE", "A little grit. Or a lot.", 0xE7956B, 3, {{"Level", "%", 0, 100, 1}, {"Gain", "%", 0, 100, 1}, {"Tone", "%", 0, 100, 1}}},
    {"AMP", "Find your starting point.", 0xE9B76E, 5, {{"Gain", "%", 0, 100, 1}, {"Bass", "%", 0, 100, 1}, {"Middle", "%", 0, 100, 1}, {"Treble", "%", 0, 100, 1}, {"Level", "%", 0, 100, 1}}},
    {"CHORUS", "A wider shade of your sound.", 0x86BCA9, 3, {{"Mix", "%", 0, 100, 1}, {"Rate", " Hz", 1, 100, 1}, {"Depth", "%", 0, 100, 1}}},
    {"DELAY", "Give every note a little space.", 0x83AFDC, 3, {{"Mix", "%", 0, 100, 1}, {"Time", " ms", 20, 1500, 10}, {"Feedback", "%", 0, 95, 1}}},
    {"REVERB", "From a small room to open air.", 0xB49DD5, 3, {{"Mix", "%", 0, 100, 1}, {"Decay", " s", 1, 100, 1}, {"Damping", "%", 0, 100, 1}}}
};
const char *amp_voices[3] = {"American Clean", "British Chime", "British Stack"};
const char *amp_voice_details[3] = {"'65 Twin Reverb inspired", "AC30 inspired", "Marshall 800 inspired"};
const char *amp_preset_names[3] = {"Preset 1", "Preset 2", "Preset 3"};
void amp_factory_tone(int preset, amp_tone_t *tone)
{
    static const int defaults[AMP_BLOCK_COUNT][5] = {{-55,120}, {65,20,40}, {55,35,55}, {32,50,45,62,65}, {25,12,40}, {22,380,30}, {28,24,45}};
    memset(tone, 0, sizeof(*tone));
    memcpy(tone->value, defaults, sizeof(defaults));
    tone->voice = preset;
    tone->enabled[AMP_AMP] = tone->enabled[AMP_REVERB] = true;
    if(preset == 1) { tone->enabled[AMP_COMP] = tone->enabled[AMP_DELAY] = true; tone->value[AMP_AMP][0] = 48; }
    if(preset == 2) { tone->enabled[AMP_GATE] = tone->enabled[AMP_DRIVE] = tone->enabled[AMP_DELAY] = true; tone->value[AMP_AMP][0] = 72; tone->value[AMP_DRIVE][1] = 60; }
}
bool amp_tone_equal(const amp_tone_t *a, const amp_tone_t *b)
{
    if(a->voice != b->voice) return false;
    for(int i = 0; i < AMP_BLOCK_COUNT; i++) {
        if(a->enabled[i] != b->enabled[i]) return false;
        for(int j = 0; j < amp_blocks[i].count; j++) if(a->value[i][j] != b->value[i][j]) return false;
    }
    return true;
}
