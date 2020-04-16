 set(CMAKE_VERBOSE_MAKEFILE TRUE)
#cmake_minimum_required(VERSION 3.2)

# -------------------------------------------------------------------
# main
# -------------------------------------------------------------------
project(liboreore)

include(CTest)
enable_testing()

#if(CMAKE_BUILD_TYPE MATCHES Debug)
#	#add_compile_options(-Wall -Wextra -O0 -g --coverage)
#else()
#	#add_compile_options(-Wall -Wextra -O2)
#endif()

#set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebug")
#gtest_force_shared_crt
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(src)
add_subdirectory(googletest)
add_subdirectory(test)

