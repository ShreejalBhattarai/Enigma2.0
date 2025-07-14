cmake_minimum_required(VERSION 3.13)

# Set Pico SDK path (relative path to the pico-sdk folder)
set(PICO_SDK_PATH "${CMAKE_CURRENT_LIST_DIR}/pico-sdk")
include(${PICO_SDK_PATH}/pico_sdk_init.cmake)


project(enigma-project C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the SDK
pico_sdk_init()

# Add source files
add_executable(enigma
    Enigma2.0/src/main.c
    Enigma2.0/src/functions.c
    Enigma2.0/src/plugboard.c
    Enigma2.0/src/ui_functions.c
)

# Link Pico SDK
target_link_libraries(enigma pico_stdlib)
pico_enable_stdio_usb(enigma 1)
pico_enable_stdio_uart(enigma 0)
pico_add_extra_outputs(enigma)
