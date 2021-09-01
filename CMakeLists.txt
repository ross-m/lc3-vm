cmake_minimum_required(VERSION 3.10)

project(lc3-vm)

include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(lc3-vm "${PROJECT_SOURCE_DIR}/src/main.c" "${PROJECT_SOURCE_DIR}/src/operations.c" "${PROJECT_SOURCE_DIR}/src/traps.c" "${PROJECT_SOURCE_DIR}/src/platform.c")
