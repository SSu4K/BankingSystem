all: main

main: main.o interface.o data.o account.o
	gcc $^ -o $@

%.o : %.c 
	gcc -Wall -pedantic $^ -c


account.o: account.c account.h

data.o: data.c data.h

interface.o: interface.c interface.h

main.o: main.c interface.h

clean:
	del /f main.o data.o account.o interface.o main