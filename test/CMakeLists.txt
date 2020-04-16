# -------------------------------------------------------------------
# Test executable
# -------------------------------------------------------------------
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebug")
add_executable(
	liboreore_test
	statemachine_test.cpp
	)

target_include_directories(
	liboreore_test
	PUBLIC ${PROJECT_SOURCE_DIR}/src
	)

target_link_libraries(
	liboreore_test
	#oreore
	#gmock
	gmock_main
	#gcov
	)

#set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

add_test(
	NAME liboreore_test
	COMMAND $<TARGET_FILE:liboreore_test>
	)

