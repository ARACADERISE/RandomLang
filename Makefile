AllC = $(wildcard src/*.c)
compile = gcc -Wall -o main.o main.c

.PHONY: run
FILE = samples/first.rand
run:
	@$(compile) $(AllC) && ./main.o $(FILE)