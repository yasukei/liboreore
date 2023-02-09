BUILD_DIR:=build

.PHONY: all build test clean rebuild

all: build

build:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake .. && make

test: build
	cd $(BUILD_DIR) && ctest -V ..

clean:
	rm -rf $(BUILD_DIR)

rebuild: clean build


