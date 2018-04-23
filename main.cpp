#include<iostream>
#include"triplet.h"

using namespace std;
/*

bool mettre_a_jour(liste_adjacences& L, triplet A);

liste_adjacences chemin(liste_adjacences& L,int taille, int n);
void mettre_a_jour(liste_adjacences& L, liste_adjacences S, triplet A);
void tri(liste_adjacences L);

bool existe_chemin1(liste_adjacences L, int a, int b);
bool existe_chemin2(liste_adjacences L, int b, int a);
*/
int main(){
  triplet a;
  triplet b(1,2,4);
  cout<<"a = "; a.print(); cout<<", b = "; b.print(); cout<<endl;
  cout<<"a==b : "<<(a==b)<<endl;
  a=b;
  cout<<"a = "; a.print(); cout<<", b = "; b.print(); cout<<endl;
  cout<<"a==b : "<<(a==b)<<endl;

  liste_adjacences L;
  L.ajoutTete(b);
  L.ajoutTete(6,3,9);
  L.ajoutTete(7,8,2);
  L.ajoutTete(7,8,7);
  L.ajoutTete(1,3,1);
  L.ajoutTete(7,9,8);
  L.ajoutTete(a);
  L.print();
  cout<<"tri"<<endl;
  L.tri_decroissant();
  L.print();
  L.retirerTete();
  L.print();
  cout<<L.contient(b)<<" , "<<L.contient(triplet(1,2,5))<<endl;
  L.val_tete().print(); cout<<" ; "; L.get_tete().info.print(); cout<<endl;
  liste_adjacences L2(L);
  L2.print();
  L2.retirer_deb_fin(1,8);
  L2.tri_decroissant();
  L2.print();
  
  return 0;
}
