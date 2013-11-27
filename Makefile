CXX := g++
export OBJ_HOME := $(realpath obj)
export INCL_HOME := $(realpath include)
LIBS := -lgmp -lgmpxx
EXECUTABLE := schemecpp

.PHONY: $(EXECUTABLE)
$(EXECUTABLE): 
	cd src && $(MAKE)
	$(CXX) -Wall $(LIBS) obj/*.o obj/scriptlib/*.o -o $(EXECUTABLE)

.PHONY: clean
clean: 
	rm -f obj/*.o
	rm -f $(EXECUTABLE)
	cd src && $(MAKE) clean
