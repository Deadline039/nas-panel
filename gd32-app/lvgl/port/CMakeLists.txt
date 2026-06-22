cmake_minimum_required(VERSION 3.12.4)

set(LVGL_PORT_DIR ${CMAKE_CURRENT_LIST_DIR})
file(GLOB_RECURSE SOURCES ${LVGL_PORT_DIR}/*.c)

add_library(lvgl_port STATIC ${SOURCES})

target_include_directories(lvgl_port PUBLIC
        ${LVGL_PORT_DIR}
)

target_link_libraries(lvgl_port PUBLIC
        lvgl
        freertos_kernel
)

