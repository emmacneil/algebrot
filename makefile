SRC_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(SRC_FILES:.cpp=.o)))
CFLAGS := -g -std=c++11 -Iinclude
LFLAGS := -lSDL2
PROG_NAME := mandelbrot

all: $(OBJ_FILES)
	g++ -o $(PROG_NAME) $^ $(LFLAGS)

obj/%.o: src/%.cpp
	g++ $(CFLAGS) -c -o $@ $<

clean:
	rm obj/*.o $(PROG_NAME)
