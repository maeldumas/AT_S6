#include<iostream>
#include "liste_adjacences.h"

using namespace std;


liste_adjacences::liste_adjacences(){
  tab= new triplet[1];
  triplet a= triplet(0,0,0);
  tab[0]=a;
}



triplet* liste_adjacences::get_tab(){
  return tab;
}

int liste_adjacences::get_taille(){
  return taille;
}

triplet& liste_adjacences::at(int i){
  if((i<0) || (i>=taille)){
    cout<<"l'indice donné n'est pas valide"<<endl;
    int i;
    cin>>i;}
  else{
    return tab[i];
  }
}

void liste_adjacences::set_tab(triplet* t){
  for(int i=0; i<taille; i++)
    tab[i]=t[i]; 
}

void liste_adjacences::set_taille(int n){
  taille=n;
}

void liste_adjacences::add_triplet(triplet t){
  taille+=1;
  tab[taille-1]=t;
}

triplet liste_adjacences::tete(){
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
  if(j==-1)
    cout<<"erreur t n'appartient pas à la liste, on ne peut donc pas le supprimer"<<endl;
  else{
    for(int i=j; i<taille-1; i++)
      tab[i]=tab[i+1];
  }
  taille=taille-1;

}

void liste_adjacences::print2(){
  for(int i=0; i<taille; i++){
    tab[i].print();
    cout<<endl;
  }
}
