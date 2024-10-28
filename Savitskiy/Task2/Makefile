all: Gauss

Gauss: main.o matrix.o solveFuncs.o classMethods.o variation.o
	g++ main.o matrix.o solveFuncs.o classMethods.o variation.o -o build/Gauss -lm -pthread

matrix.o: code/matrix.cpp
	g++ -c code/matrix.cpp -Wall -Wextra -Werror -pthread

solveFuncs.o: code/solveFuncs.cpp
	g++ -c code/solveFuncs.cpp -Wall -Wextra -Werror -pthread

main.o: code/main.cpp
	g++ -c code/main.cpp -Wall -Wextra -Werror -pthread

classMethods.o: code/classMethods.cpp
	g++ -c code/classMethods.cpp -Wall -Wextra -Werror -pthread

variation.o: code/variation.cpp
	g++ -c code/variation.cpp -Wall -Wextra -Werror -pthread

fullclean: 
	rm build/* *.o

clean:
	rm *.o
