CC = g++ -Wall
PROG=main
SOURCE=main.cpp liste_adjacences.cpp triplet.cpp

all: $(PROG)

triplet.o: triplet.cpp 
	$(CC) -c triplet.cpp

liste_adjacences.o: liste_adjacences.cpp
	$(CC) -c liste_adjacences.cpp

main.o: main.cpp
	$(CC) -c main.cpp

main: $(SOURCE:.cpp=.o)
	$(CC) $(SOURCE:.cpp=.o) -o $(PROG) 
