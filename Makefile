

all: clean main execute

execute:  main a.out
	./a.out

main: main.c
	gcc -Wall main.c -lm

clean:
	rm -rf *.o
