all: Gauss


Gauss: main.o matrix.o solveFuncs.o structFuncs.o
	gcc main.o matrix.o solveFuncs.o structFuncs.o -o build/Gauss -lm -Wall -Wextra -Werror

matrix.o: code/matrix.c
	gcc -c code/matrix.c -lm -Wall -Wextra -Werror


solveFuncs.o: code/solveFuncs.c
	gcc -c code/solveFuncs.c -lm -Wall -Wextra -Werror


structFuncs.o: code/structFuncs.c
	gcc -c code/structFuncs.c -lm -Wall -Wextra -Werror


main.o: code/main.c
	gcc -c code/main.c -lm -Wall -Wextra -Werror


clean:
	rm *.o

fullclean:
	rm *.o build/Gauss