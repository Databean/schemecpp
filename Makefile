CXX := g++
export OBJ_HOME := $(realpath obj)
export INCL_HOME := $(realpath include)
LIBS := -lgmp -lgmpxx
EXECUTABLE := schemecpp
ALLCODE := $(shell find . -type f | grep -e "\(\.h\)\|\(\.cpp\)\|\(\.y\)\|\(\.l\)")

$(EXECUTABLE): $(ALLCODE)
	cd src && $(MAKE)
	$(CXX) -std=gnu++11 -Wall $(LIBS) obj/*.o obj/scriptlib/*.o -o $(EXECUTABLE)

.PHONY: clean
clean: 
	rm -f obj/*.o
	rm -f $(EXECUTABLE)
	cd src && $(MAKE) clean
