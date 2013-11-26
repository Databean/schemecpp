CC := g++
CFLAGS = -Wall -c
SOURCES := $(wildcard *.cpp)
OBJECTS := $(SOURCES:.cpp=.o)

main:  $(OBJECTS)
	

%.o: %.cpp
	g++ $(CFLAGS) $< -o $(OBJ_HOME)/scriptlib/$@ -I..

.PHONY: clean
clean:
	rm *.o