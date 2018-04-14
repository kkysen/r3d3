CFLAGS = --std=c++17 -g -ggdb -O3 -march=native -Wall -Werror
GCC = g++ $(CFLAGS)
BIN_NAME = CompactFlights
BIN_FLAGS = -pg

EMCC_FLAGS = -std=c++1z -g3 -Wall -Werror --bind -O0
EMCC = emcc $(EMCC_FLAGS)
WASM_NAME = CompactFlights.html
WASM_FLAGS = -s WASM=1 -s DEMANGLE_SUPPORT=1

CC = g++ $(CFLAGS)

SRC_DIR = src
BIN_DIR = bin
WASM_DIR = wasm

rwildcard = $(foreach d, $(wildcard $1*), $(call rwildcard, $d/, $2) $(filter $(subst *, %, $2), $d))

HEADERS = $(wildcard $(call rwildcard, $(SRC_DIR), *.h))

SRCS = $(wildcard $(call rwildcard, $(SRC_DIR), *.cpp))

BIN_OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BIN_DIR)/o/%.o, $(SRCS))
WASM_OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(WASM_DIR)/bc/%.bc, $(SRCS))

bin_dir_exists:
	mkdir -p $(BIN_DIR)
	mkdir -p $(BIN_DIR)/o
	mkdir -p $(BIN_DIR)/o/util

$(BIN_DIR)/o/%.o: $(SRC_DIR)/%.cpp
	$(GCC) -c $< -o $@

bin_obj: bin_dir_exists $(BIN_OBJS)

$(BIN_DIR)/$(BIN_NAME): $(BIN_OBJS)
	$(GCC) -o $@ $^ $(OUT_FLAGS)

all: bin_dir_exists $(BIN_DIR)/$(BIN_NAME) wasm

run: bin_dir_exists $(BIN_DIR)/$(BIN_NAME)
	./$(BIN_NAME)

clear_bin:
	rm -rf $(BIN_DIR)

clear_wasm:
	rm -rf $(WASM_DIR)

clear: clear_bin clear_wasm

wasm_dir_exists:
	mkdir -p $(WASM_DIR)
	mkdir -p $(WASM_DIR)/bc
	mkdir -p $(WASM_DIR)/bc/util

$(WASM_DIR)/bc/%.bc: $(SRC_DIR)/%.cpp
	$(EMCC) -c $< -o $@

wasm_obj: wasm_dir_exists $(WASM_OBJS)

wasm: wasm_dir_exists $(WASM_DIR)/$(WASM_NAME)

$(WASM_DIR)/$(WASM_NAME): $(WASM_OBJS)
	$(EMCC) $(WASM_FLAGS) -o $@ $^