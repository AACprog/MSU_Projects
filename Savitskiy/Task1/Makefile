all: Gauss

Gauss: main.o matrix.o rowWork.o classFuncs.o devCnt.o
	g++ main.o matrix.o rowWork.o classFuncs.o devCnt.o -o build/Gauss -lm

matrix.o: code/matrix.cpp
	g++ -c code/matrix.cpp -Wall -Wextra -Werror

rowWork.o: code/rowWork.cpp
	g++ -c code/rowWork.cpp -Wall -Wextra -Werror

main.o: code/main.cpp
	g++ -c code/main.cpp -Wall -Wextra -Werror

classFuncs.o: code/classFuncs.cpp
	g++ -c code/classFuncs.cpp -Wall -Wextra -Werror

devCnt.o: code/devCnt.cpp
	g++ -c code/devCnt.cpp -Wall -Wextra -Werror

fullclean: 
	rm build/* *.o

clean:
	rm *.o
