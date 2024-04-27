CC := g++

# PRO2 Default Jutge flags 
C_FLAGS := -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11 -fno-extended-identifiers


# Compilation rec
./target/program: ./objects/%.o 
	$(CC) $(C_FLAGS) -o ./target/program $^

./obj/%.o: ./src/%.cc ./src/%.hh
	$(CC) $(C_FLAGS) -o $@ -c $<



.PHONY = clean tar check

docs: ./src/%.cc ./src/%.hh
	doxygen Doxyfile
check: 
	./samples/checker.sh
clean:
	rm ./target/* ./objects/*
tar: clean
	rm ./upload.tar 
	tar -cvf ./upload.tar --exclude='.git' . 
