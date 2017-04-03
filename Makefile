OPTS = -g -Wall -Wextra -g3 -O0 -std=gnu++0x -fopenmp 

all : Cell.o CellA.o CellB.o Environment.o Spot.o main.o
	g++ $(OPTS) Cell.o CellA.o CellB.o Environment.o Spot.o main.o -o celllab

main.o: main.cpp
	g++ $(OPTS) -c main.cpp  

Cell.o: Cell.cpp Cell.h
	g++ $(OPTS) -c Cell.cpp 

CellA.o: CellA.cpp CellA.h
	g++ $(OPTS) -c CellA.cpp

CellB.o: CellB.cpp CellB.h
	g++ $(OPTS) -c CellB.cpp

Environment.o: Environment.cpp Environment.h
	g++ $(OPTS) -c Environment.cpp

Spot.o: Spot.cpp Spot.h
	g++ $(OPTS) -c Spot.cpp

clean : 
	rm -rf *.o celllab data.csv
	