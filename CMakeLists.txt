cmake_minimum_required(VERSION 3.10)
project(xpm-parser)

include_directories(./ ${PROJECT_SOURCE_DIR}/xpm)

enable_testing()

add_subdirectory(xpm)
add_subdirectory(tools)