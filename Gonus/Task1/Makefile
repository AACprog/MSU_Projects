all: Gauss

Gauss: classMethods.o derivation.o main.o matrix.o solveFuncs.o
	g++ classMethods.o derivation.o main.o matrix.o solveFuncs.o -o build/Gauss -lm

classMethods.o: code/classMethods.cpp
	g++ -c code/classMethods.cpp -Wall -Wextra -Werror

derivation.o: code/derivation.cpp
	g++ -c code/derivation.cpp -Wall -Wextra -Werror

main.o: code/main.cpp
	g++ -c code/main.cpp -Wall -Wextra -Werror

matrix.o: code/matrix.cpp
	g++ -c code/matrix.cpp -Wall -Wextra -Werror

solveFuncs.o: code/solveFuncs.cpp
	g++ -c code/solveFuncs.cpp -Wall -Wextra -Werror

fullclean: 
	rm build/* *.o

clean:
	rm *.o