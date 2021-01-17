
laska: laska.o 
	gcc -Wall main.c laska.o -o laska -lm --ansi --pedantic

laska.o: laska.c laska.h
	gcc -c laska.c

clean:
	rm laska
	rm laska.o