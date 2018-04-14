#include<iostream>
#include"triplet.h"

using namespace std;
triplet::triplet(): deb(0), fin(0), poids(0){
}

triplet::triplet(int a, int b, int c): deb(a), fin(b), poids(c){
}

int triplet::get_deb(){
  return deb;
}

int triplet::get_fin(){
  return fin;
}

int triplet::get_poids(){
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

triplet& triplet::operator=( triplet &t){ //si t et this différents
  int a = t.get_deb();
  int b= t.get_fin();
  int c= t.get_poids();  
  set_deb(a);
  set_fin(b);
  set_poids(c);
  return *this;
}

bool triplet::egal(triplet t){
  bool egal=false;
  int a=t.get_deb();
  int b=t.get_fin();
  int a1=get_deb();
  int b1=get_fin();
  if((a==a1) && (b==b1))
    egal=true;
  return egal;
}

void triplet::print(){
  cout<<"["<<get_deb()<<" , "<<get_fin()<<" , "<<get_poids()<<" ]"<<endl;
}


