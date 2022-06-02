main: main.o solver.o puzzleGenerator.o
	g++ -g -std=c++98  solver.o puzzleGenerator.o main.o -o main

solver.o: solver.cpp solver.h
	g++ -std=c++98 -c solver.cpp

puzzleGenerator.o: puzzleGenerator.cpp puzzleGenerator.h
	g++ -std=c++98 -c puzzleGenerator.cpp

main.o: main.cpp solver.h puzzleGenerator.h
	g++ -std=c++98 -c main.cpp

run:
	./main

clean:
	rm -f *.o *.tar main

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./main

tarfile:
	tar -cvz *.cpp *.h makefile -f sodoku.tar