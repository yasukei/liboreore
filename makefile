BUILD_DIR=build

.PHONY: all run test clean rebuild

all:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake .. && make

run: test

test: all
	$(BUILD_DIR)/test/Main

clean:
	rm -rf $(BUILD_DIR)

rebuild: clean all

