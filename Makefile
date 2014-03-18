# Libs
LIB_SYS = -lm -lrt

# Compilation Binaries
CC = g++
CFLAGS = -DDEBUG -g -Wall
LNFLAGS = $(LIB_SYS)

# Exe Name
EXE = traveling-salesman

# Sources
SRC = api.cpp main.cpp outils.cpp pvc_exact.cpp

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
