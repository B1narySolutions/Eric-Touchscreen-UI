# Edit and preview in LVGL Pro

1. In LVGL Pro, use **Open Project** and select this `ui` folder (the folder
   containing `project.xml`). If the dialog requests a file, choose `project.xml`.
2. Open **screens/home.xml**. The target is already 1024 x 600.
3. Use the live preview to select AMP or an effect. Open the corresponding
   component file to change its controls, text, sizes, or spacing.
4. Save the XML file to retain design changes. The preview refreshes from XML.

## Where to make small changes

| File | What to edit |
| --- | --- |
| `screens/home.xml` | Overall screen layout: header, signal blocks, footer, panel positions |
| `globals.xml` | Shared colors under `consts`, fonts, initial control values under `subjects` |
| `components/amp_button.xml` | Shared button styling and centered label |
| `components/signal_block.xml` | Effect selection, ON/BYPASS, and drag event connection |
| `src/amp_chain.c` | Touch reordering and left-to-right effect order for the audio engine |
| `components/parameter_dial.xml` | All dials, readouts, and plus/minus buttons |
| `components/amplifier_selector.xml` | Top model menu: Fender '65 Twin Reverb, Vox AC30, Marshall JCM800 |
| `components/amp_drawer.xml` | Header model button, dropdown animation, tap-away backdrop, and swipe dismissal |
| `components/adjustment_popup.xml` | Shared translucent right panel, large value display, vertical swipe control |
| `components/amp_panel.xml` | Five amplifier tone controls, separate from amp selection |
| `components/gate_panel.xml` through `reverb_panel.xml` | Individual effect panels |
| `components/cabinet_panel.xml` | Fixed cabinet IR selector at the output end of the chain |
| `components/preview_dialogs.xml` | Presets, settings, and preview information dialogs |

Examples: change the `amber` color in `globals.xml`; move the master slider by
editing its `x` in `home.xml`; enlarge all dials by editing their width/height
in `parameter_dial.xml`. The shared `surface` and `button_base` styles control
panel and button styling. When resizing controls, leave room for their labels.

`selected_block` chooses the visible editor: 0 gate, 1 compressor, 2 drive,
3 amp, 4 chorus, 5 delay, 6 reverb, 7 cabinet. Change its initial value in `globals.xml`
to start the full preview on a different effect. `dialog` defaults to 0;
1 shows presets, 2 settings, 3 the preview information dialog.

Press and drag an effect's upper button left or right to change its position
in the signal path. Neighboring effects snap aside as the dragged effect
crosses a slot; releasing drops it into that slot. A short tap still selects
that effect, and the lower ON/BYPASS button remains independent. The leftmost
effect receives audio first. The cabinet remains fixed after all seven movable
blocks because its impulse response represents the final speaker/cabinet stage.
The seven draggable blocks live in a dedicated bounded container, while CAB is
a sibling outside it. This prevents drag draw-order changes from overlapping CAB.
`amp_chain_get_order()` in `src/amp_chain.h`
returns the current left-to-right IDs for the future audio engine. Reordering
marks the preview as edited, but the XML preview does not save chain order to
Preset 1/2/3 or route real audio yet.

Tap the amplifier model in the header to slide its selector down. Tap outside,
use the X button, or swipe the open menu to collapse it. The menu uses a 220 ms XML
timeline; its overlay captures outside taps so they do not also edit a dial.
`sidebar_open` controls its backdrop. Its `voice` subject is independent of
`selected_block`, so changing amplifiers does not navigate away from the
current effect. Effect tabs and tone panels use the space freed on the left.

Drag a dial's outer ring to change its value directly. Tap its blank center
or its value readout to open the translucent right adjustment panel. Master
volume and AUX mix open their panels when their labels or values are tapped;
their horizontal sliders remain directly draggable. Drag up/down over the
vertical fader to raise/lower that control's value. Tap outside or X to close
the panel, keeping the new value.
The popup and original control bind to the same subject. It shows the selected
parameter and units (including ms/dB), not a generic volume for every effect.
Plus/minus buttons on the main page remain available for direct fine changes.
Presets and Settings close when tapped outside their window as well as with X.

`active_adjustment` is 0 when closed, 1-22 for effect/amp parameters, 100 for
master, and 101 for AUX. Each dial's `control_id` selects a popup instance in
`home.xml`; keep its subject, units, and bounds consistent when adding controls.
Popup opacity is `style_bg_opa="88%"` on `value_panel`; adjust it there.

The layout is in XML and the chain reordering behavior is in `src/amp_chain.c`;
the original C reference simulator still has its earlier layout until an
editor export. Physical touchscreen tuning remains to be done.

## Live preview behavior

Effect selection, bypass, amp voice selection, dials, fine adjustments, master,
mute, AUX, and simulated output routing use native XML subjects and events.
Chain dragging uses `src/amp_chain.c`, included by `user_config.cmake`. After
opening the project in LVGL Pro, use **Ctrl+B** (the hammer button) to compile
the custom C into the editor preview. The uncompiled XML-only preview shows
the initial fixed order; it cannot execute the drag callback.

Preset 1/2/3 select the displayed name only; they do not load different tones.
Save opens an explanation rather than pretending to save a tone. The original
C simulator retains its full session-based preset behavior. Rebuilding or
refreshing the XML preview can reset its live control values. To change the
initial values permanently, edit subjects in `globals.xml` and save the file.

Chorus rate and reverb decay use integer tenths, explicitly labeled `0.1 Hz`
and `0.1 s`; 12 means 1.2 Hz and 24 means 2.4 seconds.

## Exporting later

The project is named `amp_editor`. Export its C code into this `ui/` folder
using LVGL Pro. Reconfigure the root CMake project after the first export,
then build; `src/main.c` is wired to `amp_editor_init("A:ui")` and
`home_create()` when it detects the exported library. The editor's own `sim/`
entry point is also wired to `home_create()`.

The generated header/library route has not yet been built from a fresh editor
export. Before exporting, `run-prototype.ps1` opens the original C version;
XML changes do not automatically update that executable. Keep visual changes
in XML rather than editing both copies of the layout.

## Verification

All components and globals loaded without XML errors in the installed LVGL
Pro 9.5 XML preview runtime. The XML was rendered at 1024 x 600 and checked
for clipping. Existing XML interactions were exercised through pointer input.
The C drag handler passed a native LVGL 9.5 pointer test moving an effect from
the middle to the first slot and then to the last slot. The compiled LVGL Pro
editor preview still needs a local hammer build to exercise drag there.
Verification screenshots are local artifacts and are not included in the repository. The app's native automation
connection was unavailable, so verification used its preview runtime in a
local headless browser rather than the visible editor window.
