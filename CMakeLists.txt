cmake_minimum_required(VERSION 3.10)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

# Set project name and target
project(IOT_END_NODE C CXX ASM)
message("CMAKE_PROJECT_NAME: ${CMAKE_PROJECT_NAME}")

get_filename_component(CXX_COMPILER_NAME ${CMAKE_CXX_COMPILER} NAME_WE)
message("CXX_COMPILER_NAME: ${CXX_COMPILER_NAME}")

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

set(TARGET IOT_END_NODE)
set(MCU_MODEL STM32WLE5xx)

# Specify the build type (debug or release)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Set optimization flags based on the build type
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(OPT_FLAGS "-Og -g -gdwarf-2")
else()
    set(OPT_FLAGS "-O2")
endif()

# Define MCU options
set(MCU_FLAGS "-mcpu=cortex-m4 -mthumb")
set(DEFINITIONS "-DCORE_CM4" "-DUSE_HAL_DRIVER" "-DSTM32WLE5xx")

set(MIDDLEWARE_SOURCES
    Middlewares/Third_Party/SubGHz_Phy/stm32_radio_driver/lr_fhss_mac.c
    Middlewares/Third_Party/SubGHz_Phy/stm32_radio_driver/radio.c
    Middlewares/Third_Party/SubGHz_Phy/stm32_radio_driver/radio_driver.c
    Middlewares/Third_Party/SubGHz_Phy/stm32_radio_driver/radio_fw.c
    Middlewares/Third_Party/SubGHz_Phy/stm32_radio_driver/wl_lr_fhss.c
)
set(DRIVER_SOURCE
    Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_rcc.c
    Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_rcc_ex.c
    Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_flash.c
    Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_flash_ex.c
    Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_gpio.c
    Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_dma.c
    Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_dma_ex.c
    Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_pwr.c
    Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_pwr_ex.c
    Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_cortex.c
    Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal.c
    Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_exti.c
    Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_rtc.c
    Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_rtc_ex.c
    Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_subghz.c
    Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_tim.c
    Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_tim_ex.c
    Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_uart.c
    Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_uart_ex.c
    Drivers/BSP/stm32wlxx_nucleo.c
    Drivers/BSP/stm32wlxx_nucleo_radio.c
    Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_adc.c
    Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_adc_ex.c
    Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_ll_adc
    Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_iwdg.c
)

set(UTILITES_SOURCE
    Utilities/trace/adv_trace/stm32_adv_trace.c
    Utilities/misc/stm32_mem.c
    Utilities/misc/stm32_systime.c
    Utilities/misc/stm32_tiny_sscanf.c
    Utilities/misc/stm32_tiny_vsnprintf.c
    Utilities/timer/stm32_timer.c
    Utilities/lpm/tiny_lpm/stm32_lpm.c
)

# List of C source files
set(C_SOURCES
    Core/Src/adc.c
    Core/Src/adc_if.c
    Core/Src/main.c
    Core/Src/gpio.c
    Core/Src/filter.c
    Core/Src/rtc.c
    Core/Src/subghz.c
    Core/Src/user_system.c
    Core/Src/usart.c
    Core/Src/stm32wlxx_it.c
    Core/Src/stm32wlxx_hal_msp.c
    Core/Src/stm32_lpm_if.c
    Core/Src/sys_app.c
    Core/Src/timer_if.c
    Core/Src/system_stm32wlxx.c
    Core/Src/tim.c
    SubGHz_Phy/App/app_subghz_phy.c
    SubGHz_Phy/App/subghz_phy_app.c
    SubGHz_Phy/Target/radio_board_if.c
    Core/Src/usart_if.c
    Core/Src/sys_debug.c
    Core/Src/dma.c
    Utilities/sequencer/stm32_seq.c
    Core/Src/iwdg.c
)

# List of ASM source files
set(ASM_SOURCES
    startup_stm32wle5xx.s
)

# Include directories
include_directories(
    Core/Inc
    Drivers/STM32WLxx_HAL_Driver/Inc
    Drivers/STM32WLxx_HAL_Driver/Inc/Legacy
    Drivers/CMSIS/Device/ST/STM32WLxx/Include
    Drivers/BSP
    Drivers/CMSIS/Include
    SubGHz_Phy/App
    SubGHz_Phy/Target
    Utilities/trace/adv_trace
    Utilities/misc
    Utilities/timer
    Utilities/lpm/tiny_lpm
    Middlewares/Third_Party/SubGHz_Phy
    Middlewares/Third_Party/SubGHz_Phy/stm32_radio_driver
    Utilities/sequencer
)

# Compiler and linker flags
set(CMAKE_C_FLAGS "${MCU_FLAGS} ${OPT_FLAGS} -Wall -fdata-sections -ffunction-sections")
set(CMAKE_ASM_FLAGS "${MCU_FLAGS} ${OPT_FLAGS} -Wall -fdata-sections -ffunction-sections")
set(CMAKE_EXE_LINKER_FLAGS "${MCU_FLAGS} -specs=nano.specs -Wl,-Map=${TARGET}.map,--cref -Wl,--gc-sections")

# Linker script
set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/STM32WLE5XX_FLASH.ld)

if(NOT CXX_COMPILER_NAME STREQUAL "arm-none-eabi-g++")
    add_custom_target(${EXECUTABLE}
        COMMAND ${CMAKE_COMMAND} -E echo "Error: Unsupported compiler detected(${CXX_COMPILER_NAME}). Use correct compiler(arm-none-eabi-g++) by selecting the CMake kit: Mono_SFCPU"
    )
    return()
endif()

# Add executable
add_executable(${TARGET}
    ${C_SOURCES}
    ${ASM_SOURCES}
    ${MIDDLEWARE_SOURCES}
    ${DRIVER_SOURCE}
    ${UTILITES_SOURCE}
)

# Define compile definitions (MCU_MODEL)
target_compile_definitions(${TARGET} PRIVATE ${DEFINITIONS})

# Linker options
target_link_options(${TARGET} PRIVATE
    -T${LINKER_SCRIPT}
)

# target_link_options(${EXECUTABLE} PRIVATE
# -T${MCU_LINKER_SCRIPT} # Linker script to be used during the linking stage of compilation
# -Wl,-Map=${CMAKE_PROJECT_NAME}.map # Generates a memory map file during the linking stage
# -Wl,--start-group # Start searching for unresolved symbols
# -lc # Links the C standard library
# -lm # Links the math library
# -Wl,--end-group # Stop searching for unresolved symbols
# -Wl,--print-memory-usage # Print memory usage statistics after linking
# )

# Linker libraries
target_link_libraries(${TARGET} PRIVATE -lc -lm -lnosys)

# Convert ELF to HEX and BIN
add_custom_command(TARGET ${TARGET} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${TARGET}> ${TARGET}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary -S $<TARGET_FILE:${TARGET}> ${TARGET}.bin
    COMMENT "Generating HEX and BIN files..."
)

# Size information
add_custom_command(TARGET ${TARGET} POST_BUILD
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${TARGET}>
    COMMENT "Size of the binary..."
)

# Clean command
add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}
    COMMENT "Cleaning up build files..."
)
