# set(CMAKE_VERBOSE_MAKEFILE TRUE)

cmake_minimum_required(VERSION 2.8)

project(liboreore)
add_subdirectory(src)
add_subdirectory(test)

target_compile_options(oreore PUBLIC -g -Wall -Wextra -O0)
target_compile_features(oreore PUBLIC cxx_std_14)
target_compile_definitions(oreore PUBLIC MYDEBUG)


