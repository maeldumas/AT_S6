#include <vector>
#include <algorithm>
#include <iostream>
#include <time.h>

using namespace std;

int* TSP_naif(int** &T, int n){
  vector<int> permutation(n); //utiliser un int* ?
  int* permutationMax=new int[n];
  int max=0,tmax,i;
  for(int i=0; i<n; i++){
    permutation[i]=i;
    permutationMax[i]=i;
  }
  
  do{
    tmax=0;
    for(i=1;i<n;i++){
      tmax+=T[permutation[i-1]][permutation[i]];
    }
    if(tmax>max){
      max=tmax;
      for(i=0; i<n;i++){
	permutationMax[i]=permutation[i];
      }
    }
  } while ( next_permutation(permutation.begin(),permutation.end()) );
  return permutationMax;
}

//Renvoie le mot associé au chemin TSP
string SSP(int** &T,int* &TSP, string* &F, int n){
  string S=F[TSP[0]];
  for(int i=1;i<n;i++){
    S+=F[TSP[i]].substr(T[TSP[i-1]][TSP[i]]);
  }
  return S;
}

//Renvoie le poids du chemin TSP
int SSP_int(int** &T,int* &TSP, string* &F, int n){
  int S=0;
  for(int i=1;i<n;i++){
    S+=T[TSP[i-1]][TSP[i]];
  }
  return S;
}


//Version 1 de l'implémentation de l'algorithme Held-Karp
//Renvoie le chemin de poids max sous forme d'un tableau
int* TSP_DP_v1(int** &T, int n){ 
  int size=1<<n;
  int** M=new int*[size];
  M[0]=new int[n];
  for(int set=1; set<size; set++){
    M[set]=new int[n];
    for(int k=0; k<n; k++){
      if(set & (1<<k)){ //on vérifie que k soit dans set, si c'est le cas on calcule C(set,k)
	if(k==set){ //si set est un singleton, on l'initialise à 0
	  M[set][k]=0;
	}
	else{     //sinon on cherche le maximum des C(set\k,m)+d(m,k)
	  int tmax=0;
	  for(int m=0; m<n; m++){
	    if(k!=m && (set & (1<<m))){ // vérification que m est dans set et est distinct de k
	      int mk=(M[set-(1<<k)][m]+T[m][k]);
	      if(tmax<mk)
		tmax=mk;
	    }
	  }
	  M[set][k]=tmax;
	}
      }
    }
  }
  //calcul du chemin maximal
  int tmax=-1,set=size-1, pos=-1, nextpos; 
  int* MaxPath=new int[n];
  for(int k=0; k<n;k++){
    if(tmax<M[set][k]){
      tmax=M[set][k];
      pos=k;
    }
  }
  MaxPath[n-1]=pos;
  for(int i=n-2; i>=0; i--){
    set-=1<<pos;
    for(int m=0;m<n; m++){
      if(set & 1<<m){
	if(tmax==M[set][m]+T[m][pos]){
	  nextpos=m;
	}
      }
    }
    MaxPath[i]=nextpos;
    tmax-=T[nextpos][pos];
    pos=nextpos;
  }
  for(int k=0;k<size;k++){
    delete[] M[k];
  }
  delete[] M;
  return MaxPath;
}


//Version 2 de l'implémentation de l'algorithme Held-Karp
//Renvoie le chemin de poids max sous forme d'un tableau
int* TSP_DP_v2(int** &T, int n){
  int size=1<<n;
  int** M=new int*[size];
  for(int set=1; set<size; set++){
    int nbelt=0,aset=0,i=0;
     while(aset!= set){
      if(set & (1<<i)){
	aset+=(1<<i);
	nbelt++;
      }
      i++;
    }     
    M[set]=new int[nbelt];
    if(nbelt==1)
      M[set][0]=0;
    else{
  int cpt=0, k=0;
      while(cpt<nbelt){ 
	int tset=set;
	if(tset & (1<<k)){ 
	  int tsubset=tset-(1<<k), tmax=-1, cptsub=0, m=0;
	  while(cptsub<nbelt-1){ 
	    if((1<<m) & tsubset){
	      int valpath=M[tsubset][cptsub], mk=valpath+T[m][k];
	      cptsub++;
	      if(tmax<mk){
		tmax=mk;
	      }
	      M[tset][cpt]=tmax;
	    }
	    m++;
	  }
	  cpt++;
	}
	k++;
      }
    }
  }
int tmax=-1, set=size-1, pos=-1, nextpos; 
  int* MaxPath=new int[n];
  for(int k=0; k<n;k++){
    if(tmax<M[set][k]){
      tmax=M[set][k];
      pos=k;
    }
  }
  MaxPath[n-1]=pos;
  for(int i=n-2; i>=0; i--){
    set-=1<<pos;
    int cpt=0, k=0;  
    while(cpt<i+1){
      if(set & (1<<k)){ 
	if(tmax==M[set][cpt]+T[k][pos]){
	  nextpos=k;
	}
	cpt++;
      }
      k++;
    }
    MaxPath[i]=nextpos;
    tmax-=T[nextpos][pos];
    pos=nextpos;
  }

  
  for(int k=1;k<size;k++){
    delete[] M[k];
  }
  delete[] M;
  
  return MaxPath;
}


//Version sans backtracking de l'implémentation de l'algorithme Held-Karp
//Renvoie le poids du chemin de poids chemin de poids max sous forme d'un tableau

void list_subsets_bysize(int ens, int nextelement, vector<vector<int> > &T, int n, int size_set){
  if(nextelement<n){
    int enst=ens+(1<<nextelement);
    T[size_set].push_back(enst);
    list_subsets_bysize(enst, nextelement+1,T,n,size_set+1);
    list_subsets_bysize(ens, nextelement+1,T,n,size_set);
  }
}

int TSP_DP_vsb(int** &T, int n){
  if(n==0)
    return 0;
  int size=1<<n;
  int** M=new int*[size];
  vector<vector<int> > subsets(n);
  list_subsets_bysize(0,0,subsets,n,0);
  
  for(int i=0; i<n; i++){
    int set=subsets[0][i];
    M[set]=new int;
    M[set][0]=0;
  }
  for(int i=1; i<n; i++){
    for(int set=0; set<subsets[i].size();set++){ 
      M[subsets[i][set]]=new int[i+1]; 
      int cpt=0, k=0;
      while(cpt<i+1){ 
	int tset=subsets[i][set];
	if(tset & (1<<k)){ 
	  int tsubset=tset-(1<<k), tmax=-1, cptsub=0, m=0;
	  while(cptsub<i){ 
	    if((1<<m) & tsubset){
	      int valpath=M[tsubset][cptsub], mk=valpath+T[m][k];
	      cptsub++;
	      if(tmax<mk){
		tmax=mk;
	      }
	      M[tset][cpt]=tmax;
	    }
	    m++;
	  }
	  cpt++;
	}
	k++;
      }
    }
    for(int set=0; set<subsets[i-1].size();set++){
      delete[] M[subsets[i-1][set]];
    }
  
  }

   int tmax=0;
  for(int k=0; k<n;k++){
    if(tmax<M[size-1][k]){
      tmax=M[size-1][k];
    }
  }
  
   delete[] M[size-1];
  delete[] M;


  
  return tmax;
}


