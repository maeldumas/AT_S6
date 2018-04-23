#include<iostream>
#include "liste_adjacences.h"

using namespace std;


liste_adjacences::liste_adjacences(){
  tete=NULL;  
}
liste_adjacences::liste_adjacences(const liste_adjacences& L){
  tete=NULL;
  cellule *p=L.tete;
  while(p!=NULL){
    ajoutTete(p->info);
    p=p->succ;
  }
}

bool liste_adjacences::empty(){
  return tete==NULL;
}

void liste_adjacences::ajoutTete(int a, int b, int c){
  cellule *p=new cellule;
  p->info=triplet(a,b,c);
  p->succ=tete;
  tete=p;
}

void liste_adjacences::ajoutTete(triplet t){
  cellule *p=new cellule;
  p->info=triplet(t);
  p->succ=tete;
  tete=p;
}

void liste_adjacences::retirerTete(){
  if(!this->empty()){
    cellule *p=tete;
    tete=tete->succ;
    delete p;
  }
}

cellule& liste_adjacences::get_tete(){
    return *tete;
}

triplet liste_adjacences::val_tete(){
  return tete->info;
 
}

bool liste_adjacences::contient(const triplet &t){
  bool appartient=false;
  if(!this->empty()){
    cellule *p=tete;
    while(p!=NULL && !appartient){
      if(p->info==t)
	appartient=true;
      p=p->succ;
    }
  }
  return appartient;
}

void liste_adjacences::print(){
  if(!this->empty()){
    cellule *p=tete;
    while(p!=NULL){
      p->info.print();
      cout<<" ";
      p=p->succ;
    }
  }
  cout<<endl;
}

//retire de la liste d'adjacence tous les triplets t tel que  t.deb == deb et t.fin == fin
void liste_adjacences::retirer_deb_fin(int d, int f){
  cellule *p=tete;
  bool b=true;
  while(p!=NULL && b){
    if(p->info.get_deb()==d || p->info.get_fin()==f){
      cellule *q=p;
      p=p->succ;
      delete q;
    }else{
      b=false;
    }
  }
  tete=p;
  while(p!=NULL && p->succ!=NULL){
    cellule *q=p->succ;
    if(q->info.get_deb()==d || q->info.get_fin()==f){
      p->succ=q->succ;
      delete q;
    }
    else{
      p=q;

    }
  }
}

void tri_aux(cellule* &L){
  if(L!=NULL && L->succ!=NULL){
    cellule *pivot=L;
    cellule *parcours=pivot->succ;
    cellule *inf=NULL;
    cellule *sup=pivot;
    pivot->succ=NULL;
    while(parcours!=NULL){
      if(pivot->info.get_poids()>=parcours->info.get_poids()){
	cellule *t=parcours;
	if(parcours->succ!=NULL)
	  parcours=parcours->succ;
	else
	  parcours=NULL;
	t->succ=inf;
	inf=t;
      }else{
	cellule *t=parcours;
	if(parcours->succ!=NULL)
	  parcours=parcours->succ;
	else
	  parcours=NULL;
	t->succ=sup;
	sup=t;
      }
    }/*cellule *af=inf;
       cout<<"inf : ";
       while(af!=NULL){
       af->info.print(); cout<<" ";
       af=af->succ;
       }
       af=sup;
       cout<<"sup : ";
       while(af!=NULL){
       af->info.print(); cout<<" ";
       af=af->succ;
       }
       cout<<endl;*/
    tri_aux(inf);
    tri_aux(sup);
    pivot->succ=inf;
    L=sup;
  }
}

void liste_adjacences::tri_decroissant(){
  tri_aux(tete);
}

liste_adjacences::~liste_adjacences(){
  while(!this->empty())
    this->retirerTete();
}

