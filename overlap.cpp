#include <iostream>
#include <vector>
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

//renvoie la taille de l'overlap entre s1 et s2
//si s2 est entièrement recouvert par s1, renvoie -1
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
  
//Créé la matrice du graphe de chevauchement en retirant les mots entièrement recouverts
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
	  //on note si j est entièrement recouvert
	  overlaped[j]=(T[i][j]==-1 && !overlaped[i])||overlaped[j];
	}
      }
    }
  }
  //Mise à jour de la matrice en supprimant les sommets entièrement recouverts
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
