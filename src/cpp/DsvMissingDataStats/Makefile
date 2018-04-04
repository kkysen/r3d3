FLAGS = --std=c++17 -g -ggdb -O3
CC = g++ $(FLAGS)
NAME = DsvMissingDataStats
MAIN = main.cpp
LIBS = $(NAME).cpp
DEFAULT_CSV = /mnt/c/Users/Khyber/Downloads/flight-delays/flights.csv

all:
	$(CC) -o $(NAME) $(MAIN) $(LIBS)

run: all
	./$(NAME) $(DEFAULT_CSV)