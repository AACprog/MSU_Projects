all: Gauss

Gauss: classMethods.o derivation.o main.o matrix.o solveFuncs.o
	g++ classMethods.o derivation.o main.o matrix.o solveFuncs.o -o build/Gauss -lm -pthread

classMethods.o: code/classMethods.cpp
	g++ -c code/classMethods.cpp -Wall -Wextra -Werror -pthread

derivation.o: code/derivation.cpp
	g++ -c code/derivation.cpp -Wall -Wextra -Werror -pthread

main.o: code/main.cpp
	g++ -c code/main.cpp -Wall -Wextra -Werror -pthread

matrix.o: code/matrix.cpp
	g++ -c code/matrix.cpp -Wall -Wextra -Werror -pthread

solveFuncs.o: code/solveFuncs.cpp
	g++ -c code/solveFuncs.cpp -Wall -Wextra -Werror -pthread

fullclean: 
	rm build/* *.o

clean:
	rm *.o
