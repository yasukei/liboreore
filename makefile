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

clean:
	rm -rf $(BUILD_DIR)

rebuild: clean all

