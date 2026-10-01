get_filename_component(PROJECT_ROOT "${CMAKE_CURRENT_LIST_DIR}/../../.." ABSOLUTE)
set(UI_ROOT "${PROJECT_ROOT}/ui")

file(GLOB UI_COMPONENT_SOURCES "${UI_ROOT}/components/*_gen.c")
file(GLOB UI_SCREEN_SOURCES "${UI_ROOT}/screens/*_gen.c")

idf_component_register(
    SRCS
        "${UI_ROOT}/amp_editor_gen.c"
        "${UI_ROOT}/amp_editor.c"
        "${UI_ROOT}/src/amp_chain.c"
        ${UI_COMPONENT_SOURCES}
        ${UI_SCREEN_SOURCES}
    INCLUDE_DIRS "${UI_ROOT}"
    REQUIRES lvgl__lvgl
)

target_compile_definitions(${COMPONENT_LIB} PUBLIC LV_LVGL_H_INCLUDE_SIMPLE=1)
