CC=clang
CFLAGS=-std=c17 -Wall
FRAMEWORKS=-framework CoreGraphics -framework CoreFoundation -framework Carbon

BUILD_PATH=./bin
SRC=./src/main.c

$(BUILD_PATH)/bind: $(SRC)
	mkdir -p $(BUILD_PATH)
	$(CC) $(CFLAGS) $^ $(FRAMEWORKS) -o $@

clean:
	rm -rf $(BUILD_PATH)

