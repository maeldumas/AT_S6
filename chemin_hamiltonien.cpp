#include<iostream>
#include"liste_adjacences.h"

using namespace std;


//les deux premieres fonctions ne sont pas à utiliser sur une liste possédant un cycle ! sinon ça boucle
bool existe_chemin1(liste_adjacences L, int a, int b){ //n est le nombre de sommet du graphe
  bool existe=false;
  int t=L.get_taille();
  triplet k=triplet(a,b,0);
  if(L.appartient(k)){
    existe=true;}
  else{
    int u=L.voisin(a);
    int v=a;
    while(u!=-1){
      v=u;
      if(v==b){
	u=-1;}
      else{
      u=L.voisin(u);
      }
    }
    existe=(v==b);
  }
  return existe;
}

bool existe_chemin2(liste_adjacences L, int b, int a){
  bool existe=false;
  int t=L.get_taille();
  triplet k=triplet(b,a,0);
  if(L.appartient(k)){
    existe=true;}
  else{
    int u=L.voisin(b);
    int v=b;
    while(u!=-1){
      v=u;
      if(v==a){
	u=-1;}
      else{
      u=L.voisin(u);
      }
    }
    existe=(v==b);
  }
  return existe;
}

bool mettre_a_jour(liste_adjacences& L, liste_adjacences& S,triplet A, int n){
  int taille=L.get_taille();
  int a=A.get_deb();
  int b=A.get_fin();
  bool ajout=false;
  if(!(existe_chemin1(S,a,b)) && !(existe_chemin2(S,a,b))){
    for(int i=0; i<taille; i++){
      if(L.at(i).get_deb()==a){
	//L.remove_triplet(L.at(i));
	taille=taille-1;
	L.print2();
      }
    }
    for(int i=0; i<taille; i++){
      if(L.at(i).get_fin()==b){
	//	L.remove_triplet(L.at(i));
	taille=taille-1;
      }
    }
    S.add_triplet(A); 
    ajout=true;
  }
  return ajout;
}

liste_adjacences chemin(liste_adjacences& L,int taille, int n){ //n correspond au nombre total de sommets
  liste_adjacences S= liste_adjacences();
  L.print2();
  /*int cpt=0;
  triplet D=L.tete();
  S.add_triplet(D);
  for(int i=1; i<taille; i++){
    triplet A=L.at(i);
    cout<<"ajout de";
    A.print();
cout<<" :"<<mettre_a_jour(L,S,A,n)<<endl;
}*/
  /* while((cpt<n-1) && (i<taille)){
    triplet A=L.at(i);
    i++;
    int a=A.get_deb();
    int nba=0;
    for(int j=0; j<S.get_taille(); j++)
      if((S.at(j).get_deb()==a) || (S.at(j).get_fin()==a))
	nba++;
    int b=A.get_fin();
    int nbb=0;
    for(int j=0; j<S.get_taille(); j++)
      if((S.at(j).get_deb()==b) && (S.at(j).get_fin()==b))
	nbb++;
    bool ajoute=mettre_a_jour(L,S,A,n);
    if(nba==0)
      cpt+=1;
    if(nbb==0)
      cpt+=1;
      }*/
  //S.print2();
  return S;
}


