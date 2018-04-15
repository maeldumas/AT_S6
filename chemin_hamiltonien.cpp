#include<iostream>
#include"liste_adjacences.h"

using namespace std;


bool existe_chemin1(liste_adjacences L, int a, int b){
  bool existe=false;
  int n=L.get_taille();
  triplet k=triplet(a,b,0);
  if(L.appartient(k))
    existe=true;
  else{
    for(int i=0; i<n; i++){
      triplet c= triplet(a,i,0);
      if(L.appartient(c))
	existe=existe_chemin1(L,i,b);
    }
  }
  return existe;
}

bool existe_chemin2(liste_adjacences L, int b, int a){
  bool existe=false;
  int n=L.get_taille();
  triplet k=triplet(b,a,0);
  if(L.appartient(k))
    existe=true;
  else{
    for(int i=0; i<n; i++){
      triplet c= triplet(b,i,0);
      if(L.appartient(c))
	existe=existe_chemin1(L,i,a);
    }
  }
  return existe;
}

void mettre_a_jour(liste_adjacences& L, liste_adjacences S,triplet A){
  int taille=L.get_taille();
  int a=A.get_deb();
  int b=A.get_fin();
  if((existe_chemin1(S,a,b)) || (existe_chemin2(S,a,b))){
    S.remove_triplet(A);}
    else{
      for(int i=0; i<taille; i++){
	if(L.at(i).get_deb()==a){
	  L.remove_triplet(L.at(i));
	  taille=taille-1;
	  L.print2();
	}
      }
      for(int i=0; i<taille; i++){
	if(L.at(i).get_fin()==b){
	  L.remove_triplet(L.at(i));
	  taille=taille-1;
	}
      }
    }
  }

void chemin(liste_adjacences L,int taille, int n){ //n correspond au nombre total de sommets
  liste_adjacences S= liste_adjacences();
  int cpt=0;
  while(cpt<n-1){
  triplet A=L.tete();
  S.add_triplet(A);
  mettre_a_jour(L,S,A);
  cpt+=1;
  }
  S.remove_triplet(S.at(0));
}


