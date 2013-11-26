CC := g++
export OBJ_HOME := $(realpath obj)
export INCL_HOME := $(realpath include)
LIBS := -lgmp -lgmpxx
EXECUTABLE := schemecpp

.PHONY: $(EXECUTABLE)
main: 
	cd src && $(MAKE)
	$(CC) -Wall $(LIBS) obj/*.o obj/scriptlib/*.o -o main

.PHONY: clean
clean: 
	rm -f obj/*.o
	rm -f $(EXECUTABLE)
