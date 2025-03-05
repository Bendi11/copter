cmake_minimum_required(VERSION 3.30)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

project(
    bingofc
    LANGUAGES CXX
    VERSION 0.1.0
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    cmsis_core
    GIT_REPOSITORY https://github.com/STMicroelectronics/cmsis-core.git
    GIT_TAG v5.9.0
)

FetchContent_Declare(
    cmsis
    GIT_REPOSITORY https://github.com/STMicroelectronics/cmsis-device-f4.git
    GIT_TAG v2.6.10
)

FetchContent_MakeAvailable(cmsis_core cmsis)

if(NOT DEFINED ${CMAKE_TOOLCHAIN_FILE})
    include(
        arm-none-eabi
        RESULT_VARIABLE DEFAULT_TOOLCHAIN
    )
    message(INFO "Loading default toolchain ${DEFAULT_TOOLCHAIN}")
else()
    message(INFO "Using cmake toolchain ${CMAKE_TOOLCHAIN_FILE}")
endif()

file(
    GLOB_RECURSE SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

set(LINKER_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/src/system/stm32f405.x")

add_executable(${CMAKE_PROJECT_NAME} ${SRC})

target_include_directories(
    ${CMAKE_PROJECT_NAME}
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src"
    PRIVATE "${cmsis_core_SOURCE_DIR}/Include"
    PRIVATE "${cmsis_SOURCE_DIR}/Include"
)

set(CMAKE_CXX_IMPLICIT_LINK_LIBRARIES "")
set(CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES "")
SET(CMAKE_CXX_STANDARD_LIBRARIES "")
SET(CMAKE_C_STANDARD_LIBRARIES "")

target_link_options(
    ${CMAKE_PROJECT_NAME}
    PUBLIC "-T${LINKER_SCRIPT}"
    PUBLIC "--specs=nano.specs"
    PUBLIC "-nodefaultlibs"
)

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES LINK_DEPENDS ${LINKER_SCRIPT})

add_custom_command(
    TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} "-Obinary" "${CMAKE_PROJECT_NAME}.elf" "${CMAKE_PROJECT_NAME}.bin"
    COMMAND ${CMAKE_OBJCOPY} "-Oihex" "${CMAKE_PROJECT_NAME}.elf" "${CMAKE_PROJECT_NAME}.hex"
    COMMAND hex2dfu -i "${CMAKE_PROJECT_NAME}.hex" -o "${CMAKE_PROJECT_NAME}.dfu"
    COMMAND ${CMAKE_SIZE} --format=berkeley "${CMAKE_PROJECT_NAME}.elf"
)
