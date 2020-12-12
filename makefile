CC=clang
CFLAGS=-std=c99 -Wall
FRAMEWORKS=-framework CoreGraphics -framework CoreFoundation

BUILD_PATH=./bin
SRC=./src/bind.c

$(BUILD_PATH)/bind: $(SRC)
	mkdir -p $(BUILD_PATH)
	$(CC) $^ $(BUILD_FLAGS) $(FRAMEWORKS) -o $@

clean:
	rm -rf $(BUILD_PATH)

