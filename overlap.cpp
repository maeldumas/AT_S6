#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <string>


using namespace std;

void afficheMatrice(int** T, int n){
  int i,j;
  for(i=0; i<n; i++){
    for(j=0; j<n; j++){
      cout<<T[i][j]<<" ";
	}
    cout<<endl;
  }
}

void afficheMatrice_dot(int** T, int n, string* F, string filename){
  ofstream output;                           
  output.open(filename.c_str());
  output<<"digraph G{"<<endl;
  for(int i=0; i<n; i++){
    output<<i<<"[label="<<F[i]<<"];"<<endl;
  }
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      if(T[i][j]!=-1)
	output<<i<<"->"<<j<<"[label="<<T[i][j]<<"];"<<endl;
    }
  }
  output<<"}"<<endl;
   system("dot -Tpng graph.dot -o graph.png");
 
}

// il faut prendre en compte le cas où s2 est compris entièrement dans s1
int overlap_naif(string s1, string s2){
  int n1=s1.length(), n2=s2.length(), t=0, i=0, j, k;
  while(i<n1){
    k=i;
    j=0;
    while(k<n1 && j<n2 && s1[k]==s2[j]){
      k++;
      j++;
    }
    if(k==n1){
      t=n1-i;
      i=n1;
    }
    i++;
  }
  return t;
}

//version prenant en compte le recouvrement total de s2 par s1, dans ce cas là, on retourne -1
int overlap(string s1, string s2){
  int n1=s1.length(), n2=s2.length(), t=0, i=0, j, k;
  while(i<n1){
    k=i;
    j=0;
    while(k<n1 && j<n2 && s1[k]==s2[j]){
      k++;
      j++;
    }
    if(k==n1){
      t=n1-i;
      i=n1;
    }
    //on regarde le cas où le mot s2 serait entièrement inclu dans le mot s1
    if(j==n2){
      t=-1;
      i=n1;
    }
    i++;
  }
  return t;
}

//version naïve qui ne va pas supprimer les sommets entièrement recouvert par un autre sommet
void overlap_graph_naif(string* &F, int &n, int** &T){
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      if(i==j)
	T[i][j]=-1;
      else{
	T[i][j]=overlap(F[i],F[j]);
      }
    }
  }
}
//version qui va supprimer les sommets entièrement recouvert par d'autres sommets
void overlap_graph(string* &F, int &n, int** &T){
  int i,j,nt,it,jt;
  bool overlaped[n];
  for(i=0; i<n; i++)
    overlaped[i]=false;
  for(i=0; i<n; i++){
    if(!overlaped[i]){
      for(j=0; j<n; j++){
	if(i==j)
	  T[i][j]=-1;
	else{
	  T[i][j]=overlap(F[i],F[j]);
	  //on note si j est entièrement recouvert et on fait attention au cas où F[i]=F[j]
	  overlaped[j]=(T[i][j]==-1 && !overlaped[i])||overlaped[j];
	}
      }
    }
  }
  //Mise à jour de la matrice en supprimant les sommets entièrement recouvert
  i=0,it=0,nt=0;
  while(i<n){
    j=0,jt=0;
    while(overlaped[i]){
      i++;
    }
    if(i<n){
      while(j<n){
	while(overlaped[j]){
	  j++;
	}
	if(j<n){
	  T[it][jt]=T[i][j];
	  jt++; j++;
	}
      }
      nt++; it++; i++;
    }
  }  
  
  i=0,it=0;
  while(i<n){
    while(overlaped[i]){
      i++;
    }
    if(i<n){
      F[it]=F[i];
      i++; it++;
    }
  }
  n=nt;
}
/*
size_t overlap(string s1, string s2){
  size_t n1=s1.length();
  size_t n2=s2.length();
  size_t t=0;
  size_t i=0;
  size_t j=0;
  size_t deb=0;
  while(i<n1){
    //cout<<"entrée dans le while avc i="<<i<<"et j="<<j<<endl;
    if(s1[i]!=s2[j]){
      //cout<<"pas bon avec i="<<i<<endl;
      i++;
    }
    else{
      //cout<<"rentre dans le else avec i="<<i<<endl;
      deb=i;
      //cout<<"deb="<<deb<<endl;
      while((i<n1) && (j<n2) && (s1[i]==s2[j])){
	t++;
	i++;
	j++;
	//cout<<"i="<<i<<"j="<<j<<"t="<<t<<endl;
	cout<<"n1="<<n1<<endl;
	cout<<"n2="<<n2<<endl;
      }
      if((s1[i]!=s2[j]) && (deb!=n1-1) && (j!=n2) && (i!=n1)){
	i=deb+1;
	t=0;
	j=0;
	//cout<<"Remise à 0"<<endl;
      }
    }
  }
  return t;
  }

int** calcul_chevauchement(string* F, size_t n){
  int** M= new int*[n]();
  size_t i,j;
  for(i=0; i<n; i++){
    for(j=0; j<n; j++){
      if(i==j){
	M[i][j]=-1;}
      else{
	M[i][j]=overlap(F[i],F[j]);
      }
    }
  }
  return M;
  }*/
