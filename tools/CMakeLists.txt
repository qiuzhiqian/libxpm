cmake_minimum_required(VERSION 3.10)
project(xpmtools)

include_directories(./ ${PROJECT_SOURCE_DIR}/xpm)

add_executable(xpm2rgb xpm2rgb.cpp)
target_link_libraries(xpm2rgb xpm)

add_executable(xpm2png xpm2png.cpp)
target_link_libraries(xpm2png xpm png)