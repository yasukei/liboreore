#
# gtest by DownloadProject
#
include("${CMAKE_BINARY_DIR}/DownloadProject-src/DownloadProject.cmake")
download_project(
	PROJ gtest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG master
	"${UPDATE_DISCONNECTED_IF_AVAILABLE}"
	)
# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory("${gtest_SOURCE_DIR}" "${gtest_BINARY_DIR}")

add_executable(
	liboreore_test
	statemachine_test.cpp
	)
target_link_libraries(
	liboreore_test
	oreore
	gtest
	gmock
	gtest_main
	gcov
	-lprofiler -Wl,--no-as-needed -lprofiler -Wl,--as-needed
	tcmalloc
	)

add_test(
	NAME liboreore_test
	COMMAND $<TARGET_FILE:liboreore_test>
	)
set_property(
	TEST liboreore_test PROPERTY
	ENVIRONMENT CPUPROFILE=liboreore_cpu
	#ENVIRONMENT CPUPROFILE_FREQUENCY=1000
	ENVIRONMENT HEAPPROFILE=liboreore_heap
	)
