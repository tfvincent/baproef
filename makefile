all: main.o nestedLoopJoin.o sortMergeJoin.o vectorUtil.o
	g++ main.o nestedLoopJoin.o sortMergeJoin.o vectorUtil.o -lSDL2 -o main

main.o: main.cpp nestedLoopJoin.h sortMergeJoin.h
	g++ -c main.cpp -o main.o

nestedLoopJoin.o: nestedLoopJoin.cpp nestedLoopJoin.h vectorUtil.h
	g++ -c nestedLoopJoin.cpp -o nestedLoopJoin.o

sortMergeJoin.o: sortMergeJoin.cpp sortMergeJoin.h vectorUtil.h
	g++ -c sortMergeJoin.cpp -o sortMergeJoin.o

vectorUtil.o: vectorUtil.cpp
	g++ -c vectorUtil.cpp -o vectorUtil.o
