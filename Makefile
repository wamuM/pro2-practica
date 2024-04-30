
# Compilation
CC := g++ 
## PRO2 Default Jutge flags 
C_FLAGS := -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11 -fno-extended-identifiers

SRC := $(wildcard ./src/*.cc)
OBJ := $(patsubst ./src/%.cc,./objects/%.o,$(SRC))
./target/program: $(OBJ)
	$(CC) $(C_FLAGS) -o $@ $^

./objects/%.o: ./src/%.cc
	$(CC) $(C_FLAGS) -o $@ -c $<

# Other targets
.PHONY: clean tar check docs 
docs:
	doxygen Doxyfile
check: ./target/program 
	./samples/check.sh
clean:
	rm -f ./upload.tar 
	rm -rf ./docs/*
	rm -rf ./target/* ./objects/*
tar: clean docs
	tar -cvf ./upload.tar --exclude='.git' . 
