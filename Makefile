
CXX = clang++

BUILD_DIR = build

.PHONY: all configure run clean

all: build

$(BUILD_DIR)/CmakeCache.txt:
	cmake -S . -B $(BUILD_DIR) -DCMAKE_EXPORT_COMPILE_COMMANDS=ON 

configure: $(BUILD_DIR)/CmakeCache.txt

build: configure
	cmake --build $(BUILD_DIR)

run: build 
	./$(BUILD_DIR)/sorting

clean:
	rm -rf build
