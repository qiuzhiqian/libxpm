cmake_minimum_required(VERSION 3.10)
project(xpm)

include_directories(./ ${PROJECT_SOURCE_DIR}/xpm)

add_library(${PROJECT_NAME} SHARED xpm.cpp utils.cpp)

add_executable(mytest test.cpp)
target_link_libraries(mytest xpm)

add_test(
	NAME mytest 
	COMMAND $<TARGET_FILE:mytest> ${CMAKE_SOURCE_DIR}/res
	)