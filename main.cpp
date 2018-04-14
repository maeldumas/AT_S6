#include<iostream>
#include"triplet.h"
#include"liste_adjacences.h"
#include"triRapide.h"



using namespace std;


bool autorise(liste_adjacences L, liste_adjacences S, triplet A, int n);

liste_adjacences chemin(liste_adjacences L,int taille, int n);

void tri(liste_adjacences L);

int main(){
  triplet a=triplet(1,3,1);
  triplet b=triplet(1,4,2);
  triplet c=triplet(2,3,2);
  triplet d=triplet(2,5,1);
  triplet e=triplet(3,1,3);
  triplet f=triplet(3,5,1);
  triplet g=triplet(4,2,1);
  triplet h=triplet(4,5,4);
  triplet i=triplet(5,2,2);
  triplet j=triplet(5,3,1);
  int n=5;

  liste_adjacences L=liste_adjacences();
  L.add_triplet(a);
L.add_triplet(b);
L.add_triplet(c);
L.add_triplet(d);
L.add_triplet(e);
L.add_triplet(f);
L.add_triplet(g);
L.add_triplet(h);
L.add_triplet(i);
L.add_triplet(j);
int taille=L.get_taille();
 L.print2();
 /*tri(L);
 cout<<"-----------------------------------"<<endl;
 L.print2();*/
 cout<<"------------------------------"<<endl;
 triRapide(L);
 L.print2();
 //liste_adjacences S=chemin(L,taille,n);

  return 0;
}
