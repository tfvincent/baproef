all: main.o nestedLoopJoin.o sortMergeJoin.o genericJoin.o vectorUtil.o timer.o join.o
	g++ -ggdb main.o nestedLoopJoin.o sortMergeJoin.o genericJoin.o vectorUtil.o join.o timer.o -lSDL2 -o main

main.o: main.cpp nestedLoopJoin.h sortMergeJoin.h timer.h join.h
	g++ -ggdb -c main.cpp -o main.o

join.o: join.cpp join.h vectorUtil.h timer.h nestedLoopJoin.h sortMergeJoin.h
	g++ -ggdb -c join.cpp -o join.o

nestedLoopJoin.o: nestedLoopJoin.cpp nestedLoopJoin.h vectorUtil.h timer.h
	g++ -ggdb -c nestedLoopJoin.cpp -o nestedLoopJoin.o

sortMergeJoin.o: sortMergeJoin.cpp sortMergeJoin.h vectorUtil.h timer.h
	g++ -ggdb -c sortMergeJoin.cpp -o sortMergeJoin.o

genericJoin.o: genericJoin.cpp vectorUtil.h timer.h
	g++ -ggdb -c genericJoin.cpp -o genericJoin.o

vectorUtil.o: vectorUtil.cpp
	g++ -ggdb -c vectorUtil.cpp -o vectorUtil.o

timer.o: timer.cpp
	g++ -ggdb -c timer.cpp -o timer.o
