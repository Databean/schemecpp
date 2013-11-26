CC := g++
CFLAGS = -Wall -c
SOURCES := $(wildcard *.cpp)
HEADERS := $(wildcard $(INCL_HOME)/scriptlib/*.h)
OBJECTS := $(SOURCES:.cpp=.o)
INCLUDES := -I$(INCL_HOME) -I$(INCL_HOME)/scriptlib

main:  $(OBJECTS)
	
%.o: %.cpp
	g++ $(CFLAGS) $(INCLUDES) $< -o $(OBJ_HOME)/scriptlib/$@ -I..

.PHONY: clean
clean:
	rm *.o