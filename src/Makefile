CXX := g++
CFLAGS = -Wall -c -g
SOURCES := $(wildcard *.cpp)
HEADERS := $(wildcard $(INCL_HOME)/*.h)
OBJECTS := $(SOURCES:.cpp=.o) lex.yy.o y.tab.o
INCLUDES := -I$(INCL_HOME)

main:  y.tab.c lex.yy.c $(OBJECTS)
	cd scriptlib && $(MAKE)


lex.yy.c: scanner.l
	flex scanner.l

y.tab.c: parser.y
	bison -dvty parser.y

%.o: %.cpp $(HEADERS)
	$(CXX) $(CFLAGS) $(INCLUDES) $< -o $(OBJ_HOME)/$@

%.o: %.c $(HEADERS)
	$(CXX) $(CFLAGS) $(INCLUDES) $< -o $(OBJ_HOME)/$@

.PHONY: clean
clean:
	rm -f lex.yy.c
	rm -f y.tab.h
	rm -f y.tab.c