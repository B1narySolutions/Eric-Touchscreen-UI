# Guitar Amplifier Prototype

An interactive LVGL 9.5 prototype for the Waveshare ESP32-S3 Touch LCD 7B's
1024 x 600 display. The visual direction combines a pedalboard signal chain,
familiar amplifier controls, and a spacious dark touchscreen interface.

## Run on this computer

Double-click `build/bin/lvgl_simulator.exe`, or run `./run-prototype.ps1` from
PowerShell in this folder. The script rebuilds before opening the simulator.
The executable uses the native Windows display driver.

## Try it

- Select a signal block to open its controls; its separate ON/BYPASS button
  toggles processing in the simulated tone state.
- Select AMP and choose American Clean, British Chime, or British Stack.
  These are labels inspired by the brief's Twin Reverb, AC30, and Marshall 800
  targets; the prototype does not model their sound.
- Drag a dial around its arc or use the minus/plus buttons for fine adjustment.
- Save captures the complete tone in the current preset slot for this session.
- Presets opens three starting tones. Loading another tone with unsaved edits
  asks whether to discard; closing that dialog keeps the edits.
- Master volume and mute are independent of presets.
- Settings demonstrates AUX mix and headphone/speaker routing.

## Scope and integration

This is real LVGL C code, not a web mockup. `src/amp_ui.c` builds the screen;
`src/amp_model.c` defines voices, effects, preset defaults, and provisional
parameter ranges. Chorus rate and reverb decay use tenths of Hz/seconds in
their stored integer representation.

The editable version is now in `ui/`: open that folder in LVGL Pro and select
`screens/home.xml`. See `ui/EDITING.md`. The XML is the source of truth for
future visual adjustments; the original C prototype remains a reference for
its session-based preset save/recall behavior. Preview preset buttons change
the displayed preset name only, and Save explains this preview limitation.

Until XML is exported, the root simulator still calls the original C UI.
After exporting C into `ui/` and reconfiguring CMake, it loads the exported
`home` screen instead. The export path is wired but not yet built with a
fresh editor export. `--check` still tests the original C reference UI.

Audio DSP, physical output muting, battery sensing, headphone detection,
USB audio, footswitch control, and persistent storage are not connected.
Settings is explicitly a simulation; all saved presets reset on exit.
The fixed signal order is a proposed UI order, not a implemented DSP graph.
Firmware should populate telemetry from real hardware, enforce headphone
speaker routing, and connect model changes to the audio control interface.
Do not interpret these UI state changes as physical mute or output protection.

For the ESP32 port, compile `amp_ui.c` and `amp_model.c` with the board's LVGL
display and touch setup and call `amp_ui_init()` after LVGL/display initialization.
Enable Montserrat 14, 16, 24, and 28. Desktop code in `hal.c`, `main.c`, and
`preview.c` is not part of that port. Board firmware, memory use, frame rate,
and touch behavior have not been tested on the hardware.

## Validation

`build/bin/lvgl_simulator.exe --check output/prototype.ppm` runs headless
interaction checks and writes an actual LVGL screenshot. Checks cover editing
parameters across all blocks, bypass, save/recall, unsaved-edit protection,
voice selection, and master/mute state. The PPM can be converted to PNG using
Pillow. The prototype was built with GCC on Windows.

Optional scene numbers after the PPM path are: 0 = amplifier, 1 = delay,
2 = presets, 3 = settings, and 4 = unsaved-edits dialog. The `output/` folder
is generated locally and excluded from Git.

The source brief is context for the three amplifier targets and effect
parameters. Displaying a planned feature does not mean that feature has been
implemented in the audio hardware.
