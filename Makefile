CC = gcc
SRC = src/elgamal.c
TEST = tests/elgamal_tests.c
LIBS = -lgmp

elgamal_tests: $(SRC) $(TEST)
	$(CC) $(SRC) $(TEST) $(LIBS) -o elgamal_tests

clean:
	rm -f elgamal_tests
