# Libs
LIB_SYS = -lm

# Compilation Binaries
CC = g++
CFLAGS = -DDEBUG -g -Wall
LNFLAGS = $(LIB_SYS)

# Exe Name
EXE = traveling-salesman

# Sources
# TODO: add back temps.cpp and real-time library
SRC =  main.cpp api.cpp outils.cpp pvc_exact.cpp pvc_approche_ppv.cpp pvc_spanning_tree.cpp

# Objets
OBJECTS = $(SRC:%.cpp=build/%.o)

# Phony targets
.PHONY: clean run

# Rules
all: public/$(EXE)

clean:
	rm -rf build/

run: public/$(EXE)
	rm -f public/DisplayTsp.html
	cd public; ./$(EXE)

public/$(EXE): $(OBJECTS)
	$(CC) -o $@ $^ $(LNFLAGS)

# Patterns
build/%.o: src/%.cpp
	mkdir -p `dirname $@`
	$(CC) -c $(CFLAGS) -o $@ $<
