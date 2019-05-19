BUILD_DIR=build

.PHONY: all run test clean rebuild

all:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake .. && make

run: test

test: all
	cd $(BUILD_DIR) && ctest .. -V

coverage: test
	cd $(BUILD_DIR)/test \
		&& lcov -d . -c -o coverage.info \
		&& lcov -r coverage.info */googletest/* test/* */c++/* -o coverage_filtered.info \
		&& genhtml -o lcov.html coverage_filtered.info

cpu: test
	cd $(BUILD_DIR)/test \
		&& google-pprof --text liboreore_test liboreore_cpu*
	#cd $(BUILD_DIR)/test \
	#	&& google-pprof --callgrind liboreore_test liboreore_cpu* > callgrind_liboreore_cpu \
	#	&& kcachegrind callgrind_liboreore_cpu

heap: test
	cd $(BUILD_DIR)/test \
		&& google-pprof --text liboreore_test liboreore_heap*
	#cd $(BUILD_DIR)/test \
	#	&& google-pprof --callgrind liboreore_test liboreore_heap* > callgrind_liboreore_heap \
	#	&& kcachegrind callgrind_liboreore_heap

prof: cpu heap

clean:
	rm -rf $(BUILD_DIR)

rebuild: clean all

