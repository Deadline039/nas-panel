# CMake for GUI-Guider Designer
cmake_minimum_required(VERSION 3.12.4)

set(LVGL_APP_DIR ${CMAKE_CURRENT_LIST_DIR})

file(GLOB_RECURSE SOURCES ${LVGL_APP_DIR}/generated/*.c)
file(GLOB_RECURSE CUSTOM_SOURCES ${LVGL_APP_DIR}/custom/*.c)

add_library(lvgl_app STATIC ${SOURCES} ${CUSTOM_SOURCES})

target_include_directories(lvgl_app PUBLIC
        ${LVGL_APP_DIR}/generated
        ${LVGL_APP_DIR}/generated/guider_customer_fonts
        ${LVGL_APP_DIR}/generated/guider_fonts
        ${LVGL_APP_DIR}/generated/images
        ${LVGL_APP_DIR}/custom
)

target_link_libraries(lvgl_app PUBLIC
        lvgl
)
