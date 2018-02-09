SOURCES := $(wildcard src/*.cpp)
OBJECTS := $(patsubst src/%.cpp,build/%.o,$(SOURCES))
EXE := bin/core

CXX := g++
CXXFLAGS = -std=c++11 -lallegro -O2

all: $(EXE) ;
.PHONY: all

$(EXE) : $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

build/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -I./include -c $< -o $@

clean:
	rm $(OBJECTS)
.PHONY: clean
