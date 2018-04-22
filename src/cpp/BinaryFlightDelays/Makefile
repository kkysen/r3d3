FLAGS = --std=c++1z -Wall -Werror

CFLAGS = $(FLAGS) -g -ggdb -O3 -march=native
GCC = g++ $(CFLAGS)
BIN_NAME = CompactFlights
BIN_FLAGS = -pg

EMCC_DEV = -g3 -O0
EMCC_PRODUCTION = -g0 -O3
EMCC_FLAGS = $(FLAGS) --bind $(EMCC_PRODUCTION)
EMCC = emcc $(EMCC_FLAGS)
WASM_EXT = js
WASM_NAME = $(WASM_EXT)/CompactFlights.$(WASM_EXT)
WASM_DEV = -s DEMANGLE_SUPPORT=1
WASM_PRODUCTION = -s DEMANGLE_SUPPORT=0
MAX_FUNCTION_POINTERS = 20
WASM_FLAGS = -s WASM=1 -s ALLOW_MEMORY_GROWTH=1 -s "EXTRA_EXPORTED_RUNTIME_METHODS=['addFunction']" -s RESERVED_FUNCTION_POINTERS=$(MAX_FUNCTION_POINTERS) $(WASM_PRODUCTION)

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
	$(GCC) $(BIN_FLAGS) -o $@ $^

cpp: bin_dir_exists $(BIN_DIR)/$(BIN_NAME)

all: cpp wasm

run: bin_dir_exists $(BIN_DIR)/$(BIN_NAME)
	./$(BIN_NAME)

clear_bin:
	rm -rf $(BIN_DIR)

clear_wasm:
	rm -rf $(WASM_DIR)

clear_wasm_bin:
	rm -f $(WASM_DIR)/$(WASM_NAME)

clear: clear_bin clear_wasm

wasm_dir_exists:
	mkdir -p $(WASM_DIR)
	mkdir -p $(WASM_DIR)/$(WASM_EXT)
	mkdir -p $(WASM_DIR)/bc
	mkdir -p $(WASM_DIR)/bc/util

$(WASM_DIR)/bc/%.bc: $(SRC_DIR)/%.cpp
	$(EMCC) -c $< -o $@

wasm_obj: wasm_dir_exists $(WASM_OBJS)

wasm: wasm_dir_exists preprocess

$(WASM_DIR)/$(WASM_NAME): $(WASM_OBJS)
	$(EMCC) $(WASM_FLAGS) -o $@ $^

preprocess: $(WASM_DIR)/$(WASM_NAME)
	python src/scripts/preprocess.py $(WASM_DIR)/$(WASM_EXT)/CompactFlights.js

