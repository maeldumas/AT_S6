#include<iostream>
#include"liste_adjacences.h"

using namespace std;

void echanger(triplet& a, triplet& b){
  triplet c=a;
  a=b;
  b=c;
  }

void tri(liste_adjacences L){
  int n=L.get_taille();
  for(int i=0; i<n; i++)
    for(int j=0; j<n; j++)
      if(L.at(i).get_poids()>=L.at(j).get_poids())
	echanger(L.at(i), L.at(j));
}
