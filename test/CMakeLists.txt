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
	Main
	statemachine_test.cpp
	)
target_link_libraries(Main oreore gtest gmock gtest_main)

