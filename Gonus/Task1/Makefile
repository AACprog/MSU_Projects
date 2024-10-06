all: ReverseMatrix

ReverseMatrix: main.o matrix.o rowWork.o classFuncs.o fileWork.o check.o
	g++ main.o matrix.o rowWork.o classFuncs.o fileWork.o check.o -o ReverseMatrix

matrix.o: matrix.cpp
	g++ -c matrix.cpp

rowWork.o: rowWork.cpp
	g++ -c rowWork.cpp

main.o: main.cpp
	g++ -c main.cpp

classFuncs.o: classFuncs.cpp
	g++ -c classFuncs.cpp

fileWork.o: fileWork.cpp
	g++ -c fileWork.cpp

check.o: check.cpp
	g++ -c check.cpp

clean:
	rm -rf *.o gauss
