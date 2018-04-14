#include "triRapide.h"

void echanger(triplet& a, triplet& b){
  triplet c=a;
  a=b;
  b=c;
}

void triRapide_aux(liste_adjacences &L, int deb, int fin) {
  if (deb >= fin) return;
  int d = deb, f = fin-1, pivot;
  pivot = (deb + fin) / 2;
  while (d < f) {
    while ((d < pivot) && (L.at(d).get_poids()>=L.at(pivot).get_poids())) {
      d++;
    }
    while ((pivot < f) && (L.at(f).get_poids()<=L.at(pivot).get_poids())) {
      f--;
    }
    echanger(L.at(d), L.at(f));
    if (pivot == d) {
      pivot = f++;
    } else {
      if (pivot == f) {
	pivot = d--;
      }
    }
    d++;
    f--;
  }
  triRapide_aux(L, deb, pivot);
  triRapide_aux(L, pivot + 1, fin);
}

void triRapide(liste_adjacences &L){
  triRapide_aux(L, 0, L.get_taille());
}
