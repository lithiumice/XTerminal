# !!! WARNING !!! AUTO-GENERATED FILE, PLEASE DO NOT MODIFY IT AND USE
# https://docs.platformio.org/page/projectconf/section_env_build.html#build-flags
#
# If you need to override existing CMake configuration or add extra,
# please create `CMakeListsUser.txt` in the root of project.
# The `CMakeListsUser.txt` will not be overwritten by PlatformIO.

cmake_minimum_required(VERSION 3.13)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

project("Peak-ESP32-fw" C CXX)

include(CMakeListsPrivate.txt)

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/CMakeListsUser.txt)
include(CMakeListsUser.txt)
endif()

include_directories("${CMAKE_CURRENT_LIST_DIR}/lib/ArduinoJson")
include_directories("${CMAKE_CURRENT_LIST_DIR}/lib/lvgl")
include_directories("${CMAKE_CURRENT_LIST_DIR}/lib/lv_demos")
include_directories("${CMAKE_CURRENT_LIST_DIR}/lib/MPU6050")
include_directories("${CMAKE_CURRENT_LIST_DIR}/lib/NimBLE")
include_directories("${CMAKE_CURRENT_LIST_DIR}/lib/SD")
include_directories("${CMAKE_CURRENT_LIST_DIR}/lib/SPI")
include_directories("${CMAKE_CURRENT_LIST_DIR}/lib/TFT_eSPI")
include_directories("${CMAKE_CURRENT_LIST_DIR}/lib/ESP32Time")
include_directories("${CMAKE_CURRENT_LIST_DIR}/lib/Arduino-MPU6050")

add_custom_target(
    Production ALL
    COMMAND platformio -c clion run "$<$<NOT:$<CONFIG:All>>:-e${CMAKE_BUILD_TYPE}>"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    Debug ALL
    COMMAND platformio -c clion run --target debug "$<$<NOT:$<CONFIG:All>>:-e${CMAKE_BUILD_TYPE}>"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(Z_DUMMY_TARGET ${SRC_LIST})
