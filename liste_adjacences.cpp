#include<iostream>
#include "liste_adjacences.h"
#include<vector>

using namespace std;


liste_adjacences::liste_adjacences(){
  tab= new triplet[1];
  triplet a= triplet(0,0,0);
  tab[0]=a;
  taille=1;
}



triplet* liste_adjacences::get_tab(){
  return tab;
}

int liste_adjacences::get_taille(){
  return taille;
}

void liste_adjacences::set_tab(triplet* t, int n){ 
  delete tab;
  taille=n;
  tab= new triplet[taille];
  for(int i=0; i<n; i++)
    tab[i]=t[i];
}

void liste_adjacences::set_taille(int n){
  taille=n;
}

triplet& liste_adjacences::at(int i){
  if((i>=0) && (i<taille)){
    return tab[i];
  }
  else{
    cout<<"l'indice donné n'est pas valide i="<<i<<endl;
    int i;
    cin>>i;
  }
}

void liste_adjacences::add_triplet(triplet t){
  //on regarde si la liste était vide cad triplet (0,0,0)
  if((taille==1) && (tab[0].get_deb()==0) && (tab[0].get_fin()==0)){
    tab[0]=t;
  }
  //si c'est pas le cas
  else{
    //on ajoute le triplet
    taille+=1;
    tab[taille-1]=t;
  }
}

triplet& liste_adjacences::tete(){
    return tab[0];
}

bool liste_adjacences::appartient(triplet t){
  bool appartient=false;
  for(int i=0; i<taille; i++)
    if(tab[i].egal(t))
      appartient=true;
  return appartient;
  }

int liste_adjacences::get_indice(triplet t){
  int a=-1;
  for(int i=0; i<taille; i++)
    if(tab[i].egal(t))
      a=i;
  return a;
}

void liste_adjacences::remove_triplet(triplet t){
  int j=get_indice(t);
  //on vérifie l'indice
  if((j==-1) || (j>=taille))
    cout<<"erreur t n'appartient pas à la liste, on ne peut donc pas le supprimer"<<endl;
  //si  c'est valide
  else{
    t=tab[j];
    //on recopie le reste du tableau en décalant d'une case avant
    for(int i=j; i<taille-1; i++)
      tab[i]=tab[i+1];
    //on fait diminuer la taille
    taille=taille-1;
  }
}

void liste_adjacences::print2(){
  for(int i=0; i<taille; i++){
    tab[i].print();
    cout<<endl;
  }
}

int liste_adjacences::voisin(int i){
  int v=-1; //-1 ne correspond à aucun sommet donc si i n'a pas de voisin c'est pratique
  for(int j=0; j<taille; j++){
    triplet c=tab[j];
    if(c.get_deb()==i)
      v=c.get_fin();
    }
  return v;
}

int liste_adjacences::precedent(int i){
  int v=-1; //idem
  for(int j=0; j<taille; j++){
    triplet c=triplet(j,i,0);
    if(appartient(c))
      v=j;
  }
  return v;
}

liste_adjacences& liste_adjacences::operator=(liste_adjacences& L){ //si L et this différents
  int t=L.get_taille();
  triplet* tr= L.get_tab();
  set_taille(t);
  set_tab(tr,t);
  return *this;

}

liste_adjacences::~liste_adjacences(){delete[] tab;}
