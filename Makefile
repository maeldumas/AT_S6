CC = g++ 
PROG=main
SOURCE=main.cpp overlap.cpp 

all: $(PROG)

overlap.o: overlap.cpp
				$(CC) -c overlap.cpp
main.o: main.cpp overlap.cpp
				$(CC) -c main.cpp overlap.cpp

main: $(SOURCE:.cpp=.o)
				$(CC) $(SOURCE:.cpp=.o) -o $(PROG)