all: gauss

gauss: main.o matrix.o rowWork.o classFuncs.o devCnt.o
	g++ main.o matrix.o rowWork.o classFuncs.o devCnt.o -o build/gauss && rm *.o

matrix.o: code/matrix.cpp
	g++ -c code/matrix.cpp

rowWork.o: code/rowWork.cpp
	g++ -c code/rowWork.cpp

main.o: code/main.cpp
	g++ -c code/main.cpp

classFuncs.o: code/classFuncs.cpp
	g++ -c code/classFuncs.cpp

devCnt.o: code/devCnt.cpp
	g++ -c code/devCnt.cpp

clean:
	rm -rf *.o gauss
