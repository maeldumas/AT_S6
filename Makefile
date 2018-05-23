CC = g++ 
PROG=ssp
SOURCE=main.cpp overlap.cpp TSP.cpp 

all: $(PROG)

overlap.o: overlap.cpp
				$(CC) -c overlap.cpp
TSP.o: TSP.cpp
				$(CC) -c TSP.cpp
main.o: main.cpp overlap.cpp
				$(CC) -c main.cpp overlap.cpp TSP.cpp

ssp: $(SOURCE:.cpp=.o)
				$(CC) $(SOURCE:.cpp=.o) -o $(PROG)


