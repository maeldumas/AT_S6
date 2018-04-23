#ifndef __LISTE_ADJACENCES_H
#define __LISTE_ADJACENCES_H

#include "triplet.h"
#include<vector>

struct cellule {
  triplet info;
  struct cellule *succ;};

class liste_adjacences{
 private:
  cellule* tete;

 public:

  liste_adjacences();
  liste_adjacences(const liste_adjacences&);
~liste_adjacences();

 bool empty();
 void ajoutTete(int, int, int);
 void ajoutTete(triplet);
 void retirerTete();

 //retourne la cellule pointé par la tête (contient triplet et successeur
 cellule& get_tete();
 //retourne le triplet en tête
 triplet val_tete();
 
 bool contient(const triplet&);

 //retire de la liste d'adjacence tous les triplets t tel que  t.deb == deb et t.fin == fin
 void retirer_deb_fin(int, int);

 void tri_decroissant();
 
 void print();
};

#endif
