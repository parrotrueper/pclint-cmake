
add_custom_target(lint)

set(PCL_DIR "/opt/pclp")
set(XML_LNT "${PCL_DIR}/lnt/env-xml.lnt")
set(PCLINT "${PCL_DIR}/pclp64_linux")
set(PCL_CFG "${PCL_DIR}/config/pclp_config.py")
set(PCL_GREP "generate-reports.py")

# build dir
cmake_path(SET BUILD_DIR "${CMAKE_BINARY_DIR}")

# PC lint compiler configuration parameters
# compilers for the host and the target
set(HOST_COMP "/usr/bin/gcc")
set(ARM_COMP "/opt/st/stm32cubeide_1.16.0/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.12.3.rel1.linux64_1.0.200.202406132123/tools/bin/arm-none-eabi-gcc")

# compiler
set(PCFG_COMP "--compiler=gcc")
# C options
set(PCFG_COPT "--compiler-c-options='-std=gnu11'")
# C++ options
set(PCFG_CPPOPT "--compiler-cpp-options='-std=c++20'")
# compiler database
set(PCFG_CDB "--compiler-database=${PCL_DIR}/config/compilers.yaml")
# architecture
set(PCFG_ARCH_ARM "--compiler-options=-mcpu=cortex-m7")
set(PCFG_ARCH_HOST "")
# output files
set(COMP_H "${BUILD_DIR}/co-gcc.h")
set(COMP_LNT "${BUILD_DIR}/co-gcc.lnt")
set(PCFG_LNTOUT "--config-output-lnt-file=${COMP_LNT}")
set(PCFG_HOUT "--config-output-header-file=${COMP_H}")


# pc lint helper
# armhost      - parameter for the compiler config script, valid values:
#                  * arm - for elves
#                  * host - for tests
# sources      - source files to lint
# include_dirs - header dirs to lint
# defines      - #defines needed to lint
# lib_dirs     - includes NOT to lint
# result       - html result file
function (add_pc_lint
            armhost sources include_dirs defines lib_dirs result)
    # includes we do not want to lint -- these need to go before sources
    foreach (include IN LISTS lib_dirs)
        file(TO_NATIVE_PATH "${include}" include)
        set(__filedata "${__filedata}\n--i\"${include}\"\n+libdir(\"${include}\")")
    endforeach ()

    # headers we want to lint
    foreach (include IN LISTS include_dirs)
        file(TO_NATIVE_PATH "${include}" include)
        set(__filedata "${__filedata}\n-i\"${include}\"")
    endforeach ()

    # defines
    string(REPLACE "-D" "-d" defines "${defines}")
    foreach (define IN LISTS defines)
        string(FIND "${define}" "-d" def_pos)
        if(def_pos GREATER_EQUAL 0)
            set(__filedata "${__filedata}\n${define}")
        else(def_pos GREATER_EQUAL 0)
            set(__filedata "${__filedata}\n-d${define}")
        endif(def_pos GREATER_EQUAL 0)
    endforeach ()

    # sources we want to lint
    foreach (source IN LISTS sources)
        file(TO_NATIVE_PATH "${source}" source)
        set(__filedata "${__filedata}\n${source}")
    endforeach ()

    # complete the 'project.lnt' file
    file(WRITE "${BUILD_DIR}/project.lnt" ${__filedata})
    file(TO_NATIVE_PATH "${BUILD_DIR}/project.lnt" __target_settings_file)

    # check what compiler we want to configurate
    if(${armhost} STREQUAL "arm")
        set(PCFG_CBIN "--compiler-bin=${ARM_COMP}")
        set(PCFG_ARCH ${PCFG_ARCH_ARM})
    else()
        set(PCFG_CBIN "--compiler-bin=${HOST_COMP}")
        set(PCFG_ARCH ${PCFG_ARCH_HOST})
    endif()

    # path where generate-reports.py lives
    cmake_path(SET LH_DIR NORMALIZE "${FIRMWARE_ROOT_PATH}linter")
    # path where bash helper script lives
    set(LINTER_CFG "${LH_DIR}/run-pc-lint-cfg")

    # options common to all our projects
    set(OPT_LNT "${LH_DIR}/loptions.lnt")
    # our customised misra options
    set(MISRA_LNT "${LH_DIR}/au-misra3.lnt")
    # project settings
    set(PROJ_LNT "${BUILD_DIR}/project.lnt")

    set(TOHTML "${LH_DIR}/${PCL_GREP}")
    set(OUT_FILE "${BUILD_DIR}/lint_results.html")


    add_custom_target(pclint
        # compiler configuration
        COMMAND python3 ${PCL_CFG} ${PCFG_COMP} ${PCFG_CBIN} ${PCFG_COPT} ${PCFG_CPPOPT} ${PCFG_ARCH} ${PCFG_CDB} ${PCFG_LNTOUT} ${PCFG_HOUT} --generate-compiler-config
        # pc lint
        COMMAND ${PCLINT} -os[${BUILD_DIR}/lint_results.xml] ${XML_LNT} ${OPT_LNT} ${MISRA_LNT} ${COMP_LNT} ${PROJ_LNT}
        # format to html
        COMMAND python3 ${TOHTML} --input-xml "${BUILD_DIR}/lint_results.xml" --output-html ${result}
    )
    add_dependencies(lint pclint)
endfunction ()

