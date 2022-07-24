COMPILER = gcc
FLAGS = -o
NAME = j
MAIN = ./src/main.c

test:
	clear
	make clean
	make compile
	./j tests/test1.j

compile: $(MAIN)
	$(COMPILER) $(FLAGS) $(NAME) $(MAIN) $(filter-out ./src/main.c,$(wildcard ./src/*.c))

debug:
	$(COMPILER) $(FLAGS) $(NAME) $(MAIN) $(filter-out ./src/main.c,$(wildcard ./src/*.c)) -g
	gdb j

clean:
	rm -f j
	rm -rf j.dSYM


time: 
	make compile
	time ./j tests/test1.j

