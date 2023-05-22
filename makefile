all: main

main: main.o interface.o data.o account.o
	gcc -fsanitize=undefined -g $^ -o $@

.c.o: 
	gcc -fsanitize=undefined -g -Wall -pedantic -c  $<


account.o: account.h account.c

data.o: data.h data.c account.h

interface.o: interface.h interface.c data.h

main.o: main.c data.h account.h

clean:
	-rm main.o data.o account.o interface.o main