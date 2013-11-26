CC := g++
CFLAGS = -Wall -c
SOURCES := $(wildcard *.cpp)
OBJECTS := $(SOURCES:.cpp=.o) lex.yy.o y.tab.o

main:  y.tab.c lex.yy.c $(OBJECTS)
	cd scriptlib && $(MAKE)


lex.yy.c: scanner.l
	flex scanner.l

y.tab.c: parser.y
	bison -dvty parser.y

%.o: %.cpp
	g++ $(CFLAGS) $< -o $(OBJ_HOME)/$@

%.o: %.c
	g++ $(CFLAGS) $< -o $(OBJ_HOME)/$@

.PHONY: clean
clean:
	rm lex.yy.c
	rm y.tab.h
	rm y.tab.c
	rm *.o