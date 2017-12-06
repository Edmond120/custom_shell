term: input.o data_structures/dqueue.o
	gcc -o term main.c input.o data_structures/dqueue.o -lncurses

run: term
	./term

data_structures/dqueue.o:
	gcc -c data_structures/dqueue.c -o data_structures/dqueue.o

input.o:
	gcc -c input.c -lncurses

clean:
	rm data_structures/*.o
	rm *.o
	rm term
