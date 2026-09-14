set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

set(PREFIX "arm-none-eabi-")

if (WIN32)
    MESSAGE(STATUS "Now is windows!")
    set(CMAKE_C_COMPILER ${PREFIX}gcc.exe)
    set(CMAKE_CXX_COMPILER ${PREFIX}g++.exe)
    set(CMAKE_ASM_COMPILER ${PREFIX}gcc.exe)
    set(CMAKE_AR ${PREFIX}ar.exe)
    set(CMAKE_OBJCOPY ${PREFIX}objcopy.exe)
    set(CMAKE_OBJDUMP ${PREFIX}objdump.exe)
    set(SIZE ${PREFIX}size.exe)
elseif (UNIX)
    MESSAGE(STATUS "Now is UNIX-like OS!")
    set(CMAKE_C_COMPILER ${PREFIX}gcc)
    set(CMAKE_CXX_COMPILER ${PREFIX}g++)
    set(CMAKE_ASM_COMPILER ${PREFIX}gcc)
    set(CMAKE_AR ${PREFIX}ar)
    set(CMAKE_OBJCOPY ${PREFIX}objcopy)
    set(CMAKE_OBJDUMP ${PREFIX}objdump)
    set(SIZE ${PREFIX}size)
else ()
    MESSAGE(STATUS "Unsupported system!")
endif ()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_STANDARD 23)

cmake_minimum_required(VERSION 3.20)
project(nas-panel C CXX ASM)

add_compile_options(
        -mcpu=cortex-m4
        -mfpu=fpv4-sp-d16
        -mfloat-abi=hard
        -mthumb
)

add_compile_options(
        -ffunction-sections
        -fdata-sections
        -funsigned-char
        -fno-common
        -ffast-math
        --specs=nano.specs
        --specs=nosys.specs
        -MMD
)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    message(STATUS "Maximum optimization for speed")
    add_compile_options(-Ofast -flto)
    add_link_options(-flto)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    message(STATUS "Debug mode")
    add_compile_options(-Og -g)
    add_definitions(-DDEBUG)
else ()
    message(STATUS "Minimal optimization, debug info included")
    add_compile_options(-Og -g)
endif ()

add_compile_options(-Wall)

include_directories(
        App/Inc
        Bsp

        Firmware/CMSIS
        Firmware/CMSIS/GD/GD32F30x/Include
        Firmware/GD32F30x_standard_peripheral/Include

        GD32F30x_usbd_library/class/device/hid/Include
        GD32F30x_usbd_library/device/Include
        GD32F30x_usbd_library/usbd/Include
)

add_definitions(
        -DGD32F30X_XD
)

file(GLOB_RECURSE SOURCES
        "App/Src/*.c"
        "Bsp/*.c"

        "Firmware/CMSIS/GD/GD32F30x/Source/system_gd32f30x.c"
        "Firmware/CMSIS/GD/GD32F30x/Source/GCC/newlib/syscalls.c"
        "Firmware/CMSIS/GD/GD32F30x/Source/GCC/startup_gd32f30x_xd.S"
        "Firmware/GD32F30x_standard_peripheral/Source/*.c"

        "GD32F30x_usbd_library/class/device/hid/Source/custom_hid_core.c"
        "GD32F30x_usbd_library/device/Source/*.c"
        "GD32F30x_usbd_library/usbd/Source/*.c"
)

## FreeRTOS Configuration #####################################################
add_library(freertos_config INTERFACE)
target_include_directories(freertos_config
        INTERFACE
        "App/Inc"
)
set(FREERTOS_KERNEL_PATH ${CMAKE_CURRENT_LIST_DIR}/FreeRTOS)
set(FREERTOS_HEAP "4" CACHE STRING "" FORCE)
set(FREERTOS_PORT "GCC_ARM_CM4F" CACHE STRING "" FORCE)
add_subdirectory(FreeRTOS)
## End of FreeRTOS ############################################################

set(LVGL_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR}/lvgl)
add_subdirectory(lvgl)
add_subdirectory(lvgl/app)
add_subdirectory(lvgl/port)

set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/Firmware/CMSIS/GD/GD32F30x/Source/GCC/Ld/gd32f303xG_flash.ld)

add_link_options(
        -mcpu=cortex-m4
        -mfpu=fpv4-sp-d16
        -mfloat-abi=hard
        -mthumb
        -Wl,--gc-sections
        -Wl,--print-memory-usage
        --specs=nano.specs
        --specs=nosys.specs
        -Wl,-Map=${PROJECT_NAME}.map
)

add_link_options(-T ${LINKER_SCRIPT})

add_executable(${PROJECT_NAME}.elf ${SOURCES} ${LINKER_SCRIPT})

target_link_options(${PROJECT_NAME}.elf PRIVATE
        "-Wl,--no-warn-rwx-segments"
)

target_link_libraries(${PROJECT_NAME}.elf PRIVATE
        freertos_kernel
        lvgl
        lvgl_app
        lvgl_port
)

set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)
set(LST_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.lst)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
        COMMAND ${CMAKE_OBJDUMP} --all-headers --demangle --disassemble $<TARGET_FILE:${PROJECT_NAME}.elf> > ${LST_FILE}
        COMMENT "Building ${HEX_FILE}\nBuilding ${BIN_FILE}"
)
