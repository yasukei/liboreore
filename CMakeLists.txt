# set(CMAKE_VERBOSE_MAKEFILE TRUE)
cmake_minimum_required(VERSION 3.2)

# -------------------------------------------------------------------
# DownloadProject
# -------------------------------------------------------------------
configure_file(CMakeLists.txt.in DownloadProject/CMakeLists.txt)
execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
	WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/DownloadProject" )
execute_process(COMMAND "${CMAKE_COMMAND}" --build .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/DownloadProject" )

# -------------------------------------------------------------------
# main
# -------------------------------------------------------------------
project(liboreore)

option(PROFILE "Performance profile" OFF)
if(PROFILE MATCHES OFF)
	#set(MEMORYCHECK_COMMAND_OPTIONS "--gen-suppressions=all --leak-check=full --show-leak-kinds=all")
	#set(MEMORYCHECK_COMMAND_OPTIONS "--suppressions=${CMAKE_SOURCE_DIR}/test/valgrind.suppression --leak-check=full --show-leak-kinds=all")
	set(MEMORYCHECK_COMMAND_OPTIONS "--leak-check=full --show-leak-kinds=all")
endif()

include(CTest)
enable_testing()

if(CMAKE_BUILD_TYPE MATCHES Debug)
	add_compile_options(-Wall -Wextra -O0 -g --coverage)
else()
	add_compile_options(-Wall -Wextra -O2)
endif()

add_subdirectory(src)
add_subdirectory(test)

