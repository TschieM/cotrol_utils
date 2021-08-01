cmake_minimum_required(VERSION 3.10)
project(filters VERSION 0.0.1 LANGUAGES C)

add_library(filters src/butterworthFilter.c)

target_include_directories(filters
	PUBLIC
	$<INSTALL_INTERFACE:inc>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
)

install(
	TARGETS filters
	EXPORT filters-export
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
)

