#include<iostream>
#include"triplet.h"

using namespace std;
triplet::triplet(): deb(0), fin(0), poids(0){
}

triplet::triplet(int a, int b, int c): deb(a), fin(b), poids(c){
}

triplet::triplet(const triplet &t): deb(t.deb), fin(t.fin), poids(t.poids){
}

int triplet::get_deb()const {
  return deb;
}

int triplet::get_fin()const {
  return fin;
}

int triplet::get_poids()const {
  return poids;
}

void triplet::set_deb(int a){
  deb=a;
}

void triplet::set_fin(int b){
  fin=b;
}

void triplet::set_poids(int c){
 poids=c;
}

triplet& triplet::operator=(const triplet &t){ //si t et this différents
  this->deb=t.get_deb();
  this->fin=t.get_fin();
  this->poids= t.get_poids();  
  return *this;
}

bool triplet::operator==(const triplet &t){
  return (this->deb==t.get_deb() && this->fin==t.get_fin() && this->poids==t.get_poids());
}

void triplet::print(){
  cout<<"["<<get_deb()<<" , "<<get_fin()<<" , "<<get_poids()<<" ]";
}


