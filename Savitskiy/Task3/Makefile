all: Jacobi

Jacobi: main.o matrix.o solution.o
	g++ main.o matrix.o solution.o -o build/Jacobi -lm

main.o: code/main.cpp
	g++ -c code/main.cpp

matrix.o: code/matrix.cpp
	g++ -c code/matrix.cpp

solution.o: code/solution.cpp
	g++ -c code/solution.cpp

clean:
	rm *.o

fullclean:
	rm *.o build/Jacobi