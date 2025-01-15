cmake_minimum_required(VERSION 3.26)

# Include local cmake folder for extensions
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

project(cyos C ASM)

set(CMAKE_C_FLAGS "-std-c11")

# If need for cmake debug, the next line can help
# set(CMAKE_VERBOSE_MAKEFILE 1)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../output)

set(SOURCE_FILES Kernel/kernel.c Common/io.c)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_compile_options(${PROJECT_NAME} PRIVATE -I$ENV{Z88DK_HOME}/include -Isrc/ -vn -m)
target_link_options(${PROJECT_NAME} PRIVATE -m -create-app -subtype=default)

# Fixes the k7 format for old z88dk versions.
set(INPUT_FOR_FIX ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.k7)
set(ZERO_FILE ${CMAKE_SOURCE_DIR}/zero-file)
set(OUTPUT_FOR_FIX ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.fix.k7)

add_custom_command(OUTPUT k7_fix
        DEPENDS ${PROJECT_NAME}
        COMMAND ${CMAKE_COMMAND} -E cat ${INPUT_FOR_FIX} ${ZERO_FILE} > ${OUTPUT_FOR_FIX}
)

add_custom_target(${PROJECT_NAME}-fix ALL DEPENDS k7_fix)
