all: main

main: main.o data.o account.o
	gcc -fsanitize=undefined -g $^ -o $@

.c.o: 
	gcc -fsanitize=undefined -g -Wall -pedantic -c  $<


account.o: account.h account.c

data.o: data.h data.c account.h

main.o: main.c data.h account.h

clean:
	-rm main.o data.o account.o main