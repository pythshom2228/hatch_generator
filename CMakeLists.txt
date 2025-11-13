cmake_minimum_required (VERSION 3.12)

project (hatch_generator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCES 
	main.cpp
	hatch_generator.cpp
	session.cpp
	math_linear.cpp
	shape.cpp
)

add_executable (hatch_generator ${SOURCES})
target_include_directories(hatch_generator PRIVATE ${CMAKE_SOURCE_DIR}/external/)

if(MSVC)
	target_compile_options(hatch_generator PUBLIC /W4)
else()
	target_compile_options(hatch_generator PUBLIC -Wall -Wextra)
endif()