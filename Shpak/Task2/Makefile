all: Gauss


Gauss: main.o matrix.o solveFuncs.o structFuncs.o
	gcc main.o matrix.o solveFuncs.o structFuncs.o -o build/Gauss -lm -Wall -Wextra -Werror -pthread

matrix.o: code/matrix.c
	gcc -c code/matrix.c -lm -Wall -Wextra -Werror -pthread


solveFuncs.o: code/solveFuncs.c
	gcc -c code/solveFuncs.c -lm -Wall -Wextra -Werror -pthread


structFuncs.o: code/structFuncs.c
	gcc -c code/structFuncs.c -lm -Wall -Wextra -Werror -pthread


main.o: code/main.c
	gcc -c code/main.c -lm -Wall -Wextra -Werror -pthread


clean:
	rm *.o

fullclean:
	rm *.o build/Gauss