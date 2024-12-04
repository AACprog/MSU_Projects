all: Gauss


Gauss: main.o matrix.o solveFuncs.o structFuncs.o
	g++ main.o matrix.o solveFuncs.o structFuncs.o -o build/Gauss -lm -Wall -Wextra -Werror  -pthread

matrix.o: code/matrix.cpp
	g++ -c code/matrix.cpp -lm -Wall -Wextra -Werror -pthread


solveFuncs.o: code/solveFuncs.cpp
	g++ -c code/solveFuncs.cpp -lm -Wall -Wextra -Werror -pthread


structFuncs.o: code/structFuncs.cpp
	g++ -c code/structFuncs.cpp -lm -Wall -Wextra -Werror -pthread


main.o: code/main.cpp
	g++ -c code/main.cpp -lm -Wall -Wextra -Werror -pthread


clean:
	rm *.o

fullclean:
	rm *.o build/Gauss