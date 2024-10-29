all: task2

task2: main.o funcs.o 
	gcc main.o funcs.o -o build/task2

main.o: code/main.c
	gcc -c code/main.c

funcs.o: code/funcs.c
	gcc -c code/funcs.c

clean:
	rm -rf *.o build/task2