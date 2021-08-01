cmake_minimum_required(VERSION 3.10)

# set the project name
project(libControl
	VERSION 0.0.1
	DESCRIPTION
	"Controller library")

add_subdirectory(filters)

install(
	EXPORT filters-export
	FILE filtersTargets.cmake
	NAMESPACE filters::
	DESTINATION lib/cmake/filters
)

install(
	FILES filters/inc/butterworthFilter.h	
	DESTINATION "include/filters"
)

install(
	FILES filters/cmake/filtersConfig.cmake
	DESTINATION "lib/cmake/filters"
)
