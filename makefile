all: main.o nestedLoopJoin.o sortMergeJoin.o vectorUtil.o timer.o
	g++ main.o nestedLoopJoin.o sortMergeJoin.o vectorUtil.o timer.o -lSDL2 -o main

main.o: main.cpp nestedLoopJoin.h sortMergeJoin.h timer.h
	g++ -c main.cpp -o main.o

nestedLoopJoin.o: nestedLoopJoin.cpp nestedLoopJoin.h vectorUtil.h timer.h
	g++ -c nestedLoopJoin.cpp -o nestedLoopJoin.o

sortMergeJoin.o: sortMergeJoin.cpp sortMergeJoin.h vectorUtil.h timer.h
	g++ -c sortMergeJoin.cpp -o sortMergeJoin.o

vectorUtil.o: vectorUtil.cpp
	g++ -c vectorUtil.cpp -o vectorUtil.o

timer.o: timer.cpp
	g++ -c timer.cpp -o timer.o