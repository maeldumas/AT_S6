#ifndef __LISTE_ADJACENCES_H
#define __LISTE_ADJACENCES_H

#include "triplet.h"
#include<vector>

class liste_adjacences{
 private:
  triplet* tab;
  int taille;


 public:

  liste_adjacences();
~liste_adjacences();
  triplet* get_tab();
  int get_taille();



triplet& at(int i);

 void set_tab(triplet* t, int n);  //remplace tab par un tableau qui peut etre de taille différente
  
void set_taille(int n);

void add_triplet(triplet t);
triplet& tete();
bool appartient(triplet t);
void remove_triplet(triplet t);
int get_indice(triplet t);

void print2();

int voisin(int i); //redonne le voisin du sommet i c'est à dire le sommet au bout de l'arc commençant par i dans le cas où i à un seul arc sortant (si plusieurs alors il donne le dernier dans la liste)

int precedent(int j); // redonne le voisin du sommet j c'est à dire le sommet au debut de l'arc finissant par j dans le cas où j à un seul arc entrant (si plusieurs alors il donne le dernier dans la liste)

liste_adjacences& operator=(liste_adjacences &L);
};

#endif
