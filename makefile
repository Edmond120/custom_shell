input.o:
	gcc -c input.c -lncurses

data_structures/dqueue.o:
	gcc -c data_structures/dqueue.c

clean:
	rm data_structures/*.o
	rm *.o
	rm *.out

input-test:
	gcc -o input-test.out input.c -lncurses
	./input-test.out
