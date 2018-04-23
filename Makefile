CC = g++ -Wall
PROG=main
SOURCE=chemin_hamiltonien.cpp liste_adjacences.cpp main.cpp triplet.cpp triRapide.cpp

all: $(PROG)

chemin_hamiltonien.o: chemin_hamiltonien.cpp  
				$(CC) -c chemin_hamiltonien.cpp

main.o: main.cpp
				$(CC) -c main.cpp

liste_adjacences.o: liste_adjacences.cpp
				$(CC) -c liste_adjacences.cpp

triplet.o: triplet.cpp 
				$(CC) -c triplet.cpp

triRapide.o: triRapide.cpp
				$(CC) -c triRapide.cpp

main: $(SOURCE:.cpp=.o)
				$(CC) $(SOURCE:.cpp=.o) -o $(PROG) 
