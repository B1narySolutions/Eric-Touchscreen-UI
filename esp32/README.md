# Waveshare ESP32-S3-Touch-LCD-7B firmware

This ESP-IDF target displays the same generated LVGL Pro UI used by the desktop
simulator. The editable project remains in `../ui`; do not move it into this
folder. LVGL Pro continues to open `ui/project.xml`, while this firmware compiles
the generated `ui/*_gen.c` files.

The display, GT911 touch reset sequence, RGB timing and pin mapping are based on
Waveshare's official `17_lvgl_v9_demo` for the ESP32-S3-Touch-LCD-7B. The copied
driver files retain Waveshare's Apache-2.0 license in `WAVESHARE-LICENSE.txt`.

## Requirements

- ESP-IDF 5.5 or newer
- Waveshare ESP32-S3-Touch-LCD-7B with the touch panel fitted
- A data-capable USB-C cable

## Keep the editor and firmware synchronized

1. Open `../ui` in LVGL Pro and make visual changes in the XML files.
2. Press **Ctrl+B** in LVGL Pro to regenerate the `*_gen.c` and `*_gen.h` files.
3. Build this firmware. Its `amp_ui` component reads those generated files
   directly, so there is no second UI copy to update.

The Montserrat font is stored in the firmware's SPIFFS image at
`main/assets/fonts/Montserrat_Medium.ttf`. If the font file changes in LVGL Pro,
copy the updated file from `../ui/fonts` into that assets folder before flashing.

## Configure, build and flash

Open an ESP-IDF terminal, then run from this folder:

```powershell
idf.py set-target esp32s3
idf.py build
idf.py -p COM5 flash monitor
```

Replace `COM5` with the board's port. If flashing does not begin, hold **BOOT**,
tap **RESET**, start the flash command, and then release **BOOT**.

The `flash` target also writes the SPIFFS font partition. A normal application-
only flash that omits the storage partition will leave an older font image on
the board.

## Memory and display choices

- The panel runs at its native 1024x600 resolution in RGB565.
- RGB frame buffers are allocated in the board's 8 MB PSRAM.
- LVGL refreshes near 60 Hz (`16 ms`) and uses two software draw units.
- The UI task has a 16 KB stack allocated in PSRAM.
- Wi-Fi, Bluetooth and audio processing are intentionally absent from this
  display firmware. The future Daisy Seed3 control link belongs in a separate
  task and must not block the LVGL task.

## First hardware checks

After flashing, confirm the following before adding Seed3 communication:

1. The complete 1024x600 screen is visible without horizontal drift.
2. Touch coordinates align at all four corners.
3. Knobs, master volume, dialogs and the amplifier drawer respond correctly.
4. Effect blocks reorder without crossing the fixed CAB block.
5. The interface runs for at least 30 minutes without a reset or visible tear.
