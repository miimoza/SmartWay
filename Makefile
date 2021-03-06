CC=g++
CXXFLAGS=-Wall -Wextra -pedantic -std=c++17 -Iinclude -g
SRC=src/create_graph.cc src/main.cc src/station.cc src/utils.cc src/log.cc \
	src/itinerary.cc 
BIN=SmartWay

all:
	$(CC) $(CXXFLAGS) $(SRC) -o $(BIN)

clean:
	$(RM) $(BIN) *.dot *.png
