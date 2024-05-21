# Compiler
CC := g++ 
## PRO2 Default Jutge flags 
C_FLAGS := -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11 -fno-extended-identifiers

# Default target set to the executable
.DEFAULT_GOAL := ./target/program

# Compilation Targets:
SRC := $(wildcard ./src/*.cc)
OBJ := $(patsubst ./src/%.cc,./objects/%.o,$(SRC))
./target/program: $(OBJ)
	$(CC) $(C_FLAGS) -o $@ $^
	chmod 755 ./target/program
	echo Executable generated at ./target/program

./objects/%.o: ./src/%.cc
	$(CC) $(C_FLAGS) -o $@ -c $<

# Other targets
.PHONY: clean tar check docs move

## Generates docs
docs:
	doxygen Doxyfile
## Checks i/o samples against code
check: ./target/program 
	./samples/check.sh

## Cleans the codebase (same logic as in .gitignore)
clean:
	rm -f ./practica.tar 
	rm -rf ./docs/*
	rm -rf ./target/* ./objects/*

## Packs-up the code
stage: 
	./stage.sh
