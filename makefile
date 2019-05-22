# -------------------------------------------------------------------
# Variables
# -------------------------------------------------------------------
BUILD_DIR:=build
BUILD_TYPE:=Debug
PROFILE:=OFF
MEMCHECK:=-T memcheck

# -------------------------------------------------------------------
# Targets
# -------------------------------------------------------------------
.PHONY: all debug release build test run lcov profile clean rebuild

all: debug

debug: BUILD_TYPE:=Debug
debug: build

release: BUILD_TYPE:=Release
release: build

build:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake .. -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) -DPROFILE=$(PROFILE) && make

test: debug
	cd $(BUILD_DIR) && ctest .. -V $(MEMCHECK)

run: test

lcov: test
	cd $(BUILD_DIR)/test \
		&& lcov -d . -c -o coverage.info \
		&& lcov -r coverage.info */googletest/* test/* */c++/* -o coverage_filtered.info \
		&& genhtml -o lcov.html coverage_filtered.info

profile: PROFILE:=ON	# Profile and memcheck are mutual exclusive
profile: MEMCHECK:=
profile: test
	cd $(BUILD_DIR)/test \
		&& google-pprof --text liboreore_test liboreore_cpu*
	cd $(BUILD_DIR)/test \
		&& google-pprof --text liboreore_test liboreore_heap*
	#cd $(BUILD_DIR)/test \
	#	&& google-pprof --callgrind liboreore_test liboreore_heap* > callgrind_liboreore_heap \
	#	&& kcachegrind callgrind_liboreore_heap
	#cd $(BUILD_DIR)/test \
	#	&& google-pprof --callgrind liboreore_test liboreore_cpu* > callgrind_liboreore_cpu \
	#	&& kcachegrind callgrind_liboreore_cpu

clean:
	rm -rf $(BUILD_DIR)

rebuild: clean all

