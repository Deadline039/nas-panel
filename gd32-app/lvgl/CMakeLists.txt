cmake_minimum_required(VERSION 3.12.4)

file(GLOB_RECURSE SOURCES
        ${LVGL_ROOT_DIR}/src/*.c
)
add_library(lvgl STATIC ${SOURCES})

target_compile_definitions(lvgl PUBLIC
        LV_LVGL_H_INCLUDE_SIMPLE
)
target_include_directories(lvgl PUBLIC
        ${LVGL_ROOT_DIR}
)

target_link_libraries(lvgl PUBLIC
        freertos_kernel
)

