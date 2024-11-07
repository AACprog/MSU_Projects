all: Gauss

Gauss: main.o matrix.o solveFuncs.o classMethods.o variation.o
	g++ main.o matrix.o solveFuncs.o classMethods.o variation.o -o build/Gauss -lm

matrix.o: code/matrix.cpp
	g++ -c code/matrix.cpp -Wall -Wextra -Werror

solveFuncs.o: code/solveFuncs.cpp
	g++ -c code/solveFuncs.cpp -Wall -Wextra -Werror

main.o: code/main.cpp
	g++ -c code/main.cpp -Wall -Wextra -Werror

classMethods.o: code/classMethods.cpp
	g++ -c code/classMethods.cpp -Wall -Wextra -Werror

variation.o: code/variation.cpp
	g++ -c code/variation.cpp -Wall -Wextra -Werror

fullclean: 
	rm build/* *.o

clean:
	rm *.o
