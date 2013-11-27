CXX := g++
CFLAGS = -Wall -c -g
SOURCES := $(wildcard *.cpp)
HEADERS := $(wildcard $(INCL_HOME)/scriptlib/*.h) $(wildcard $(INCL_HOME)/*.h)
OBJECTS := $(addprefix $(OBJ_HOME)/scriptlib/,$(SOURCES:.cpp=.o))
INCLUDES := -I$(INCL_HOME) -I$(INCL_HOME)/scriptlib

main:  $(OBJECTS)
	
$(OBJ_HOME)/scriptlib/%.o: %.cpp $(HEADERS)
	$(CXX) $(CFLAGS) $(INCLUDES) $< -o $@

.PHONY: clean
clean:
	rm *.o