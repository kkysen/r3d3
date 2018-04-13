CFLAGS = --std=c++17 -g -ggdb -O3 -march=native
CC = g++ $(CFLAGS)
NAME = CompactFlights
OUT_FLAGS = -pg

SRC_DIR = src
BIN_DIR = bin

rwildcard = $(foreach d, $(wildcard $1*), $(call rwildcard, $d/, $2) $(filter $(subst *, %, $2), $d))

HEADERS = $(wildcard $(call rwildcard, $(SRC_DIR), *.h))

SRCS = $(wildcard $(call rwildcard, $(SRC_DIR), *.cpp))

OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BIN_DIR)/%.o, $(SRCS))

bin_dir_exists:
	mkdir -p $(BIN_DIR)
	mkdir -p $(BIN_DIR)/util

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -c $< -o $@

obj: bin_dir_exists $(OBJS)

$(NAME): $(OBJS)
	$(CC) -o $@ $^ $(OUT_FLAGS)

all: bin_dir_exists $(NAME)

run: all
	./$(NAME)

clear:
	rm -rf $(BIN_DIR)