# -------------------------------------------------------------------
# Library
# -------------------------------------------------------------------
add_library(
	oreore
	oreore.cpp
	)

target_include_directories(
	oreore
	PUBLIC ${PROJECT_SOURCE_DIR}/src
	)

target_compile_features(oreore PUBLIC cxx_std_14)

if(CMAKE_BUILD_TYPE MATCHES Debug)
	target_compile_definitions(oreore PUBLIC MYDEBUG)
endif()
