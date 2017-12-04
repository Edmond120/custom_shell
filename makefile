term: input.o data_structures/dqueue.o
	gcc -o term main.c input.o data_structures/dqueue.o -lncurses

run: term
	./term

input.o:
	gcc -c input.c -lncurses

data_structures/dqueue.o:
	gcc -c data_structures/dqueue.c -o data_structures/dqueue.o

clean:
	rm data_structures/*.o
	rm *.o
	rm term
