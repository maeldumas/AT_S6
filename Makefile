CC = g++ 
PROG=main
SOURCE=main.cpp overlap.cpp TSP.cpp 

all: $(PROG)

overlap.o: overlap.cpp
				$(CC) -c overlap.cpp
TSP.o: TSP.cpp
				$(CC) -c TSP.cpp
main.o: main.cpp overlap.cpp
				$(CC) -c main.cpp overlap.cpp TSP.cpp

main: $(SOURCE:.cpp=.o)
				$(CC) $(SOURCE:.cpp=.o) -o $(PROG)


