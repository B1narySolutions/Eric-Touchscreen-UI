# ESP32 touchscreen profiling

Enabled by `amp_profile_attach()` in main.c and `amp_profile_start()` after
screen creation. The `amp_prof` serial tag reports five-second windows from
a separate priority-1 task. Hot paths only collect microsecond timestamps and
update counters; they do not print. Generated UI and managed sources are not
modified. CMake uses link-time wrappers for public functions and LVGL display
events for render and flush timing.

Each active section prints count (`n`), average and maximum milliseconds,
total milliseconds, and calls taking at least 16 ms (`slow`). Unused sections
are omitted. Startup screen creation appears only in the first window.

| Section | Meaning |
| --- | --- |
| lvgl.timer_handler | Complete LVGL timer-processing pass, including input and rendering |
| lvgl.handler_interval | Time between starts of timer-handler passes, including sleep/scheduling |
| input.process | Touch input timer, including reading and input event processing |
| touch.gt911_read | GT911 driver read, including hardware communication |
| touch.adapter_read | Adapter's full touch callback and coordinate/state conversion |
| touch.poll_interval | Time between touch callback starts |
| ui.layout | Public layout-update calls, including chain layout |
| ui.subject_update | Public integer subject updates and synchronous observer notifications |
| event.pressed | Press event dispatch and its callbacks |
| event.pressing | Held/drag event dispatch and its callbacks |
| event.released | Release or press-lost event dispatch and its callbacks |
| event.clicked | Click/short-click event dispatch and its callbacks |
| event.gesture | Gesture event dispatch and its callbacks |
| event.value_changed | Value-change event dispatch and its callbacks |
| chain.drag_handler | Custom effect reorder handler |
| startup.home_create | Initial screen construction |
| display.refresh_cycle | Entire LVGL refresh cycle, including idle cycles |
| display.render | LVGL software rendering |
| display.render_excluding_flush | Render interval minus time in synchronous flush callbacks; still elapsed time, not CPU-only time |
| display.flush_submit | Flush callback duration; submission, not physical scanout completion |
| display.flush_wait | Time inside LVGL's flush-wait callback |
| touch.sample_to_render_ready | Oldest changed touch sample to the next render-ready event |

Additional diagnostics: pressed samples, moved samples, render events per second,
free internal SRAM, free PSRAM, and largest free internal SRAM block.
`geometry` rows count checks and position changes of the editor panels and the
ON/BYPASS buttons/labels. Checks use coordinates relative to each parent, so
intentional effect reordering does not count as a label movement. `last` identifies
the last affected editor or effect block. These checks help distinguish widget
movement from RGB scanout corruption; they do not inspect the physical image.

## Interpretation

- Timings are inclusive and overlap. Do not add all totals to estimate CPU use.
- The two interval rows include sleep and scheduling. A 30 ms interval is not a
  30 ms execution cost; the 16 ms slow counter is not an error indication.
- Render rate counts LVGL render events. It is not the LCD scanout refresh rate
  and is expected to fall while the screen is idle.
- Sample-to-render-ready is a software proxy, not physical touch-to-photon
  latency. A no-redraw refresh clears pending touches to reduce unrelated-redraw
  contamination. Use it alongside render, input, and polling measurements.
- Link wrappers cover references between compiled objects. Internal calls in a
  function's defining object can bypass wrappers; enclosing input/refresh/timer
  sections still capture their elapsed time.
- Timestamp and counter overhead remains in this diagnostic build. Serial output
  is batched to reduce interference; runtime overhead is not yet measured.

For useful logs, capture idle windows and separate windows while dragging a dial,
dragging Master, opening popups/tabs, and reordering an effect. Compare average,
maximum, and slow counts for each interaction before optimizing.
