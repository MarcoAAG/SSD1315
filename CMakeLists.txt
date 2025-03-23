# Minimum required version of CMake
cmake_minimum_required(VERSION 3.22)

# Project name
project(template)

# Specify the target system
set(CMAKE_SYSTEM_NAME Linux)  # Cross-compilation for ARM on a Linux host
set(CMAKE_SYSTEM_PROCESSOR arm)  # Specify the ARM processor architecture

# Set the ARM toolchain (gcc and g++) for C and C++ files
set(CMAKE_C_COMPILER $ENV{HOME}/Tools/gcc-arm/gcc-arm-none-eabi-10.3-2021.10/bin/arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER $ENV{HOME}/Tools/gcc-arm/gcc-arm-none-eabi-10.3-2021.10/bin/arm-none-eabi-g++)

# Define the source files for the project
set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/template_appl.c         # Main application
    ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32l0xx_hal_msp.c     # Hardware abstraction layer (HAL) MSP functions
    ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32l0xx_it.c          # Interrupt handler
    ${CMAKE_CURRENT_SOURCE_DIR}/src/system_stm32l0xx.c      # System initialization
    ${CMAKE_CURRENT_SOURCE_DIR}/src/startup.c               # Startup code
)

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include  # Header files
    ${CMAKE_CURRENT_SOURCE_DIR}/conf     # Configuration files
)

# Compiler flags for the project
# -mcpu=cortex-m0plus: Target ARM Cortex-M0+ CPU
# -O2: Optimization level 2 (balance between performance and compilation time)
# -g: Include debugging information
# -Wall: Enable all compiler warnings
# -std=c11: Use the C11 standard
# -Wl,-Map=output.map: Generate a linker map file for memory layout inspection
set(CMAKE_C_FLAGS "-mcpu=cortex-m0plus \
                   -O2 \
                   -g \
                   -Wall \
                   -std=c11 \
                   -Wl,-Map=output.map"
)

# Linker flags
# -T: Specify the custom linker script to control memory mapping
# -nostartfiles: Do not use the standard startup files
set(CMAKE_EXE_LINKER_FLAGS "-T ${CMAKE_CURRENT_SOURCE_DIR}/linker/linker.ld \
                            -nostartfiles"
)

# Add subdirectory for the STM32 HAL library
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/STM32L0xx_HAL_ST stm32l0xx_hal_st)

# Define the executable target for the project
# This will compile and link the sources into the final executable
add_executable(${PROJECT_NAME}_appl.out ${SOURCES})

# Link the executable with the STM32 HAL library
target_link_libraries(${PROJECT_NAME}_appl.out 
    stm32l0xx_hal_st  # STM32 HAL static library
)
