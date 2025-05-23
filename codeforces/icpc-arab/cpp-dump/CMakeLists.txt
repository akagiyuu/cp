cmake_minimum_required(VERSION 3.12)

project(
    cpp-dump
    DESCRIPTION "A C++ library for debugging purposes that can print any variable, even user-defined types."
    HOMEPAGE_URL "https://github.com/philip82148/cpp-dump"
    LANGUAGES CXX
)

# Library
add_library(cpp-dump INTERFACE)
target_include_directories(cpp-dump INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

# Install
include(GNUInstallDirs)
install(
    FILES "cpp-dump.hpp"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)
install(
    DIRECTORY "cpp-dump"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" IS_TOP_LEVEL)

# Tests
if(IS_TOP_LEVEL)
    enable_testing()

    if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        add_compile_options(-W4 /Zc:__cplusplus)
        set(rtti_flag "")
    else()
        add_compile_options(-Wall -Wextra -Wfloat-equal -Wconversion -Wno-sign-conversion -Werror -Wshadow -fno-rtti)
        set(rtti_flag -frtti)
    endif()

    # static test
    add_executable(static_test test/static_test.cpp test/odr_test.cpp)

    # dump indent test
    add_executable(dump_indent_test test/dump_indent_test.cpp)

    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        target_compile_definitions(dump_indent_test PRIVATE USE_BITS_STDC)
    endif()

    set(args_array "normal\;160\;4" "narrow\;20\;4" "wide\;4000\;4" "shallow\;4000\;0")

    foreach(args ${args_array})
        list(GET args 0 suffix)

        add_test(
            NAME "dump-indent-${suffix}"
            COMMAND "${CMAKE_COMMAND}"
            -D "test_dir=${CMAKE_CURRENT_LIST_DIR}/test"
            -D "cmd_path=$<TARGET_FILE:dump_indent_test>"
            -D "cmd_args=${args}"
            -P "${CMAKE_CURRENT_LIST_DIR}/test/dump_indent_test.cmake"
        )
    endforeach()

    # dump non variable test
    add_executable(dump_non_variable_test test/dump_non_variable_test.cpp)
    add_test(
        NAME "dump-non-variable"
        COMMAND "${CMAKE_COMMAND}"
        -D "test_dir=${CMAKE_CURRENT_LIST_DIR}/test"
        -D "cmd_path=$<TARGET_FILE:dump_non_variable_test>"
        -D "compiler_id=${CMAKE_CXX_COMPILER_ID}"
        -P "${CMAKE_CURRENT_LIST_DIR}/test/dump_non_variable_test.cmake"
    )

    # dump variable test
    add_executable(dump_variable_test test/dump_variable_test.cpp)
    add_test(
        NAME "dump-variable"
        COMMAND "${CMAKE_COMMAND}"
        -D "test_dir=${CMAKE_CURRENT_LIST_DIR}/test"
        -D "cmd_path=$<TARGET_FILE:dump_variable_test>"
        -D "compiler_id=${CMAKE_CXX_COMPILER_ID}"
        -P "${CMAKE_CURRENT_LIST_DIR}/test/dump_variable_test.cmake"
    )

    # color indent test
    set(args_array "normal_original\;160\;4\;1" "shallow_original\;4000\;0\;1" "normal_by_syntax\;160\;4\;2" "shallow_by_syntax\;4000\;0\;2")

    foreach(args ${args_array})
        list(GET args 0 suffix)

        add_test(
            NAME "color-indent-${suffix}"
            COMMAND "${CMAKE_COMMAND}"
            -D "test_dir=${CMAKE_CURRENT_LIST_DIR}/test"
            -D "cmd_path=$<TARGET_FILE:dump_indent_test>"
            -D "cmd_args=${args}"
            -P "${CMAKE_CURRENT_LIST_DIR}/test/color_indent_test.cmake"
        )
    endforeach()

    # color non variable test
    add_executable(color_non_variable_test test/color_non_variable_test.cpp)
    set(args_array "original\;1" "by_syntax\;2")

    foreach(args ${args_array})
        list(GET args 0 suffix)

        add_test(
            NAME "color-non-variable-${suffix}"
            COMMAND "${CMAKE_COMMAND}"
            -D "test_dir=${CMAKE_CURRENT_LIST_DIR}/test"
            -D "cmd_path=$<TARGET_FILE:color_non_variable_test>"
            -D "cmd_args=${args}"
            -P "${CMAKE_CURRENT_LIST_DIR}/test/color_non_variable_test.cmake"
        )
    endforeach()

    # color variable test
    set(args_array "original\;1" "by_syntax\;2")

    foreach(args ${args_array})
        list(GET args 0 suffix)

        add_test(
            NAME "color-variable-${suffix}"
            COMMAND "${CMAKE_COMMAND}"
            -D "test_dir=${CMAKE_CURRENT_LIST_DIR}/test"
            -D "cmd_path=$<TARGET_FILE:dump_variable_test>"
            -D "compiler_id=${CMAKE_CXX_COMPILER_ID}"
            -D "cmd_args=${args}"
            -P "${CMAKE_CURRENT_LIST_DIR}/test/color_variable_test.cmake"
        )
    endforeach()

    # color std version test
    if(CMAKE_CXX_STANDARD GREATER 17)
        add_executable(color_std_version_test test/color_std_version_test.cpp)
        add_test(
            NAME "color-std-version"
            COMMAND "${CMAKE_COMMAND}"
            -D "test_dir=${CMAKE_CURRENT_LIST_DIR}/test"
            -D "cmd_path=$<TARGET_FILE:color_std_version_test>"
            -D "std_version=${CMAKE_CXX_STANDARD}"
            -D "compiler_id=${CMAKE_CXX_COMPILER_ID}"
            -P "${CMAKE_CURRENT_LIST_DIR}/test/color_std_version_test.cmake"
        )
    endif()

    # color rtti test
    add_executable(color_rtti_test test/color_rtti_test.cpp)
    target_compile_options(color_rtti_test PRIVATE "${rtti_flag}")
    add_test(
        NAME "color-rtti"
        COMMAND "${CMAKE_COMMAND}"
        -D "test_dir=${CMAKE_CURRENT_LIST_DIR}/test"
        -D "cmd_path=$<TARGET_FILE:color_rtti_test>"
        -P "${CMAKE_CURRENT_LIST_DIR}/test/color_rtti_test.cmake"
    )

    # log label test
    add_executable(log_label_test test/log_label_test.cpp)
    add_test(
        NAME "log-label-test"
        COMMAND "${CMAKE_COMMAND}"
        -D "test_dir=${CMAKE_CURRENT_LIST_DIR}/test"
        -D "cmd_path=$<TARGET_FILE:log_label_test>"
        -P "${CMAKE_CURRENT_LIST_DIR}/test/log_label_test.cmake"
    )

    # readme test
    file(GLOB files readme/*.cpp)

    foreach(file ${files})
        get_filename_component(basename "${file}" NAME_WLE)

        add_executable("readme_${basename}" "${file}")
        add_test(
            NAME "readme-${basename}"
            COMMAND "${CMAKE_COMMAND}"
            -D "test_dir=${CMAKE_CURRENT_LIST_DIR}/test"
            -D "cmd_path=$<TARGET_FILE:readme_${basename}>"
            -D "compiler_id=${CMAKE_CXX_COMPILER_ID}"
            -D "basename=${basename}"
            -P "${CMAKE_CURRENT_LIST_DIR}/test/readme_test.cmake"
        )
    endforeach()
endif()
