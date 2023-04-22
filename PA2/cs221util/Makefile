CPP_FILES = $(wildcard *.cpp) lodepng/lodepng.cpp
OBJ_FILES = $(notdir $(CPP_FILES:.cpp=.o))
CXX = clang++

CXXFLAGS = -std=c++14 -c -g -O0 -Wall -Wextra -pedantic
LDFLAGS = -std=c++14 -lpthread -lm


all: $(OBJ_FILES)

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f *.o

.PHONY: all clean
