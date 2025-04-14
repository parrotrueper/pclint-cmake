cmake_minimum_required(VERSION 3.22)

set(PROJECT_NAME unit_tests)
set(MODULE_NAME "unit_tests")


project(${PROJECT_NAME} LANGUAGES C CXX)

find_program(BASH bash HINTS /usr/bin)

# firmware repo path NOTE!!! normalize leaves trailing '/'
cmake_path(SET FIRMWARE_ROOT_PATH NORMALIZE "${CMAKE_CURRENT_SOURCE_DIR}/..")

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(BASE_FLAGS "--coverage -MMD -pedantic -pedantic-errors -Wall -Wextra -Wshadow -Wconversion -Werror -Wdouble-promotion -Wunused -Wformat=2 -Wformat-truncation -g")
set(CMAKE_C_FLAGS "${BASE_FLAGS} -Wstrict-prototypes")
set(CMAKE_CXX_FLAGS "${BASE_FLAGS}")

enable_testing()

# path to module sources dir
set(THIS_APP_PATH "${FIRMWARE_ROOT_PATH}")
# report location
set(REPORT_PATH "${FIRMWARE_ROOT_PATH}${MODULE_NAME}")
# path to unit tests for this module
set(UTSRC_DIR ${FIRMWARE_ROOT_PATH}tests)
# path where gtest is built
set(TEST_FRAME_BUILD "/tmp/build-gtest")

# use the googletest library
set(GTEST_LOCATION /opt/googletest)
add_subdirectory(${GTEST_LOCATION} ${TEST_FRAME_BUILD})

add_compile_definitions(
    DD_TRACE_EN=0
    DD_UNIT_TESTING=1
    USING_GOOGLE_TEST
)

# ------ Headers ------
# headers for the module we are testing
set(THESE_INCLUDES
    ${THIS_APP_PATH}/hardware-drivers
    ${THIS_APP_PATH}/your-app
)
# common library headers
set(COMMON_INCLUDES
${THIS_APP_PATH}/common/counter
${THIS_APP_PATH}/common/evaluate
${THIS_APP_PATH}/common/utils
)

# ----- ALL INCLUDE PATHS -----
include_directories(
   # test and test support
   ${THIS_APP_PATH}/hardware-drivers/test_support
   # module specific and common libraries
   ${THESE_INCLUDES}
   ${COMMON_INCLUDES}
)
# ------ Sources ------
# module specific
set(THESE_SOURCES
    ${THIS_APP_PATH}/hardware-drivers/drv_Gpio.c
    ${THIS_APP_PATH}/your-app/application.c
    ${THIS_APP_PATH}/your-app/hello_world.c
)
set(COMMON_SOURCES
    ${THIS_APP_PATH}/common/counter/cCounter.c
    ${THIS_APP_PATH}/common/evaluate/cEvaluate.c
    ${THIS_APP_PATH}/common/utils/util_Crc32.c
    ${THIS_APP_PATH}/common/utils/util_DateTime.c
)

# -------- ALL SOURCE FILES --------
set(SOURCES
    # test files
    ${UTSRC_DIR}/test_2_cCounter.cpp
    ${UTSRC_DIR}/test_cCounter.cpp
    ${UTSRC_DIR}/test_cEvaluate.cpp
    ${UTSRC_DIR}/test_drv_Gpio.cpp
    ${UTSRC_DIR}/test_hello_world.cpp
    ${UTSRC_DIR}/test_application.cpp
    ${UTSRC_DIR}/test_util_Crc32.cpp
    ${UTSRC_DIR}/test_util_DateTime.cpp
    # module specific
    ${THESE_SOURCES}
    ${COMMON_SOURCES}
)
# --- build ---
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(
    ${PROJECT_NAME}
    GTest::gtest_main
    GTest::gmock_main
)

# ---- run tests and analysis tools ---
set(REPORT_OUT "${REPORT_PATH}/CCM.html")
set(COVERAGE_OUT "${REPORT_PATH}/coverage/coverage.html")
set(TEST_REPORT "${REPORT_PATH}/TestResults.json")
set(COV_EXCLUDE_REGEX ".*\.cpp")
set(LINT_REPORT "${REPORT_PATH}/tests_lint.html")
file(MAKE_DIRECTORY "${REPORT_PATH}/coverage")
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${PROJECT_NAME} --gtest_color=yes --gtest_output=json --output-on-failure
    COMMAND cat test_detail.json > ${TEST_REPORT}
    COMMAND lizard ${THESE_SOURCES} -Emccabe --CCN 7 --length 40 --output_file report.html
    COMMAND cat report.html >> ${REPORT_OUT}
    COMMAND gcovr --html-details -o ${COVERAGE_OUT} -r ${THIS_APP_PATH} -e ${COV_EXCLUDE_REGEX}
)

# pc lint helper function
include(${FIRMWARE_ROOT_PATH}linter/pcLint.cmake)
set(LINT_SOURCES ${THESE_SOURCES} ${COMMON_SOURCES})
set(LINT_INCLUDES ${THESE_INCLUDES})
set(NO_LINT_INCLUDES
    ${COMMON_INCLUDES}
    ${THIS_APP_PATH}/hardware-drivers/test_support
)
set(LINT_DEFINES
    -DDD_TRACE_EN=0
    -DDD_UNIT_TESTING=1
)
# generates file.lnt
add_pc_lint("host" "${LINT_SOURCES}" "${LINT_INCLUDES}" "${LINT_DEFINES}" "${NO_LINT_INCLUDES}" "${LINT_REPORT}")

