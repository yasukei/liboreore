# set(CMAKE_VERBOSE_MAKEFILE TRUE)
cmake_minimum_required(VERSION 3.2)

#
# DownloadProject
#
configure_file(CMakeLists.txt.in DownloadProject/CMakeLists.txt)
execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
	WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/DownloadProject" )
execute_process(COMMAND "${CMAKE_COMMAND}" --build .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/DownloadProject" )

#
# main
#
project(liboreore)
add_subdirectory(src)
add_subdirectory(test)

target_compile_options(oreore PUBLIC -g -Wall -Wextra -O0)
target_compile_features(oreore PUBLIC cxx_std_14)
target_compile_definitions(oreore PUBLIC MYDEBUG)

