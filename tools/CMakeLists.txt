cmake_minimum_required(VERSION 3.10)
project(xpm2rgb)

include_directories(./ ${PROJECT_SOURCE_DIR}/xpm)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} xpm)