CXX = g++
CPPFLAGS = -g -Wall -std=c++11
FILE = grid.cpp

all: clean grid

grid: $(FILE)
	$(CXX) $(CPPFLAGS) $^ -o $@

clean:
	rm -f $(FILE)