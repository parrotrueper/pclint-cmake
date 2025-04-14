cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

# firmware repo path
cmake_path(SET FIRMWARE_ROOT_PATH NORMALIZE "${CMAKE_CURRENT_SOURCE_DIR}/..")

# path to app sources
set(EXAMPLE_APP_PATH "${FIRMWARE_ROOT_PATH}")

# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME pnp)

# Include toolchain file
include("cmake/gcc-arm-none-eabi.cmake")

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

# PCLINT_TAG: get the list of of paths we do not wish to lint
get_directory_property(NO_LINT_INCLUDES
    DIRECTORY cmake/stm32cubemx
    lint_prop)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

# Application Sources
set(PROJECT_SOURCES
    ${FIRMWARE_ROOT_PATH}your-app/application.c
    ${FIRMWARE_ROOT_PATH}your-app/hello_world.c
)
# Shared Sources
set(SHARED_SOURCES
    ${FIRMWARE_ROOT_PATH}common/counter/cCounter.c
    ${FIRMWARE_ROOT_PATH}common/evaluate/cEvaluate.c
    ${FIRMWARE_ROOT_PATH}common/template/src/template_example.c
    ${FIRMWARE_ROOT_PATH}common/utils/util_Crc32.c
    ${FIRMWARE_ROOT_PATH}common/utils/util_DateTime.c
)

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCES}
    ${SHARED_SOURCES}
)

# Application Includes
set(PROJECT_INCLUDES
    ${FIRMWARE_ROOT_PATH}your-app
)

# Shared Includes
set(SHARED_INCLUDES
    ${FIRMWARE_ROOT_PATH}common/counter
    ${FIRMWARE_ROOT_PATH}common/evaluate
    ${FIRMWARE_ROOT_PATH}common/template/api
    ${FIRMWARE_ROOT_PATH}common/utils
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${PROJECT_INCLUDES}
    ${SHARED_INCLUDES}
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    DD_TRACE_EN=1
    DD_UNIT_TESTING=0
)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx
)

# PCLINT_TAG:
# pc lint helper function
include(${FIRMWARE_ROOT_PATH}linter/pcLint.cmake)
set(LINT_REPORT "${FIRMWARE_ROOT_PATH}${CMAKE_BUILD_TYPE}.html")
set(LINT_SOURCES ${PROJECT_SOURCES} ${SHARED_SOURCES})
set(LINT_INCLUDES ${PROJECT_INCLUDES} ${SHARED_INCLUDES})
set(LINT_DEFINES
    -DUSE_PWR_LDO_SUPPLY
    -DUSE_HAL_DRIVER
    -DSTM32H743xx
)

add_pc_lint("arm" "${LINT_SOURCES}" "${LINT_INCLUDES}" "${LINT_DEFINES}" "${NO_LINT_INCLUDES}" "${LINT_REPORT}")
