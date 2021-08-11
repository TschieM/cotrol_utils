cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_COMPILER "gcc")

add_executable(filtersFreqAnalysis.out
	testFilter.c
	${CMAKE_SOURCE_DIR}/filters/src/butterworthFilter.c	
)

target_include_directories(filtersFreqAnalysis.out
	PRIVATE
	${CMAKE_SOURCE_DIR}/filters/inc	
)

target_link_libraries(filtersFreqAnalysis.out
	m	
)
