cmake_minimum_required(VERSION 3.22)

project(stm32cubemx)
add_library(stm32cubemx INTERFACE)

# firmware repo path
cmake_path(SET FIRMWARE_ROOT_PATH NORMALIZE "${CMAKE_CURRENT_SOURCE_DIR}/../../..")

# path to stm32 shared libraries
set(COMMON_ST_LIBS "${FIRMWARE_ROOT_PATH}blinky_stm32_project")

# Enable CMake support for ASM and C languages
enable_language(C ASM)

target_compile_definitions(stm32cubemx INTERFACE
	USE_PWR_LDO_SUPPLY
	USE_HAL_DRIVER
	STM32H743xx
    $<$<CONFIG:Debug>:DEBUG>
)

set(HAL_INCLUDES
    ${COMMON_ST_LIBS}/Core/Inc
    ${COMMON_ST_LIBS}/Drivers/STM32H7xx_HAL_Driver/Inc
    ${COMMON_ST_LIBS}/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy
)
set(CMSIS_INCLUDES
    ${COMMON_ST_LIBS}/Drivers/CMSIS/Device/ST/STM32H7xx/Include
    ${COMMON_ST_LIBS}/Drivers/CMSIS/Include
)
# PCLINT_TAG:
set(PROJ_LINT_INCLUDE_LIBS ${HAL_INCLUDES} ${CMSIS_INCLUDES})
set_property(DIRECTORY PROPERTY lint_prop "${PROJ_LINT_INCLUDE_LIBS}")

target_include_directories(stm32cubemx INTERFACE
    ${HAL_INCLUDES}
    ${CMSIS_INCLUDES}
)

target_sources(stm32cubemx INTERFACE
    ${COMMON_ST_LIBS}/Core/Src/main.c
    ${COMMON_ST_LIBS}/Core/Src/stm32h7xx_it.c
    ${COMMON_ST_LIBS}/Core/Src/stm32h7xx_hal_msp.c
    ${COMMON_ST_LIBS}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_cortex.c
    ${COMMON_ST_LIBS}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr.c
    ${COMMON_ST_LIBS}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr_ex.c
    ${COMMON_ST_LIBS}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc.c
    ${COMMON_ST_LIBS}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc_ex.c
    ${COMMON_ST_LIBS}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_flash.c
    ${COMMON_ST_LIBS}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_flash_ex.c
    ${COMMON_ST_LIBS}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_gpio.c
    ${COMMON_ST_LIBS}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_hsem.c
    ${COMMON_ST_LIBS}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma.c
    ${COMMON_ST_LIBS}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma_ex.c
    ${COMMON_ST_LIBS}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_mdma.c
    ${COMMON_ST_LIBS}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal.c
    ${COMMON_ST_LIBS}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_i2c.c
    ${COMMON_ST_LIBS}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_i2c_ex.c
    ${COMMON_ST_LIBS}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_exti.c
    ${COMMON_ST_LIBS}/Core/Src/system_stm32h7xx.c
    ${COMMON_ST_LIBS}/Core/Src/sysmem.c
    ${COMMON_ST_LIBS}/Core/Src/syscalls.c
    ${COMMON_ST_LIBS}/startup_stm32h743xx.s
)


target_link_directories(stm32cubemx INTERFACE
)

target_link_libraries(stm32cubemx INTERFACE
)

# Validate that STM32CubeMX code is compatible with C standard
if(CMAKE_C_STANDARD LESS 11)
    message(ERROR "Generated code requires C11 or higher")
endif()


