BUILD_DIR=build

all:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake .. && make

run: test

test:
	$(BUILD_DIR)/test/Main

clean:
	rm -rf $(BUILD_DIR)

rebuild: clean all

