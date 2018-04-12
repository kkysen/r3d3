FLAGS = --std=c++17 -g -ggdb -O3
CC = g++ $(FLAGS)
NAME = DsvMissingDataStats
MAIN = main.cpp
LIBS = $(NAME).cpp
DEFAULT_CSV = ../../data/flight-delays/flights.csv
DEFAULT_IGNORE_COLUMNS = [26, 27, 28, 29, 30, 31]

all:
	$(CC) -o $(NAME) $(MAIN) $(LIBS)

run: all
	./$(NAME) path=$(DEFAULT_CSV) "ignoreColumns=$(DEFAULT_IGNORE_COLUMNS)"