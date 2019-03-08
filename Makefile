CC=g++
CXXFLAGS=-Wall -Wextra -pedantic -std=c++17 -Iinclude -g
SRC=src/create_graph.cc src/main.cc
BIN=SmartWay

all:
	$(CC) $(CXXFLAGS) $(SRC) -o $(BIN)

clean:
	rm $(BIN)
