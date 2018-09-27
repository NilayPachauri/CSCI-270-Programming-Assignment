CXX = g++
CPPFLAGS = -g -Wall -std=c++11
FILE = grid.cpp
EXE = grid

all: clean $(EXE)

$(EXE): $(FILE)
	$(CXX) $(CPPFLAGS) $^ -o $@

clean:
	rm -f $(EXE)