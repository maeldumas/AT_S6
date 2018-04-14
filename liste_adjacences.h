#ifndef __LISTE_ADJACENCES_H
#define __LISTE_ADJACENCES_H

#include "triplet.h"

class liste_adjacences{
 private:
  triplet* tab;
  int taille;

 public:

  liste_adjacences();

  triplet* get_tab();
  int get_taille();
triplet& at(int i);

  void set_tab(triplet* t);  //remplace tab par un tableau de meme taille
  void set_taille(int n);

  void add_triplet(triplet t);
triplet tete();
bool appartient(triplet t);
void remove_triplet(triplet t);
int get_indice(triplet t);

void print2();
};

#endif
