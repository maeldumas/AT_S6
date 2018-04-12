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
	      
   
string SSP(int** &T,int* &TSP, string* &F, int n){
  string S=F[TSP[0]];
  for(int i=1;i<n;i++){
    S+=F[TSP[i]].substr(T[TSP[i-1]][TSP[i]]);
  }
  return S;
}

int SSP_int(int** &T,int* &TSP, string* &F, int n){
  int S=0;
  for(int i=1;i<n;i++){
    S+=T[TSP[i-1]][TSP[i]];
  }
  return S;
}

int TSP_DP1(int** &T, int n){
  int size=1<<n, k, m, set, tmax, mk;
  int** M=new int*[size];
  M[0]=new int[n];
  for(set=1; set<size; set++){
    M[set]=new int[n];
    for(k=0; k<n; k++){
      if(set & (1<<k)){ //on vérifie que k soit dans set, si c'est le cas on calcule C(set,k)
	if(k==set){     //si set est un singleton, on l'initialise à 0
	  M[set][k]=0;
	}
	else{    //sinon on cherche le maximum des C(set\k,m)+d(m,k)
	  tmax=0;    
	  for(m=0; m<n; m++){
	    if(k!=m && (set & (1<<m))){ // vérification que m est dans set et est distinct de k
	      mk=(M[set-(1<<k)][m]+T[m][k]); 
	      if(tmax<mk)
		tmax=mk;
	    }
	  }
	  M[set][k]=tmax;
	}
      }
    }
    
  }
  tmax=0;
  for(k=0; k<n;k++){
    if(tmax<M[size-1][k]){
      tmax=M[size-1][k];
    }
  }
  for(k=0;k<size;k++){
    delete[] M[k];
  }
  delete[] M;
  return tmax;
}
      

int* TSP_DP2(int** &T, int n){ 
  int size=1<<n, k, m, set, tmax, mk, i;
  int** M=new int*[size];
  M[0]=new int[n];
  for(set=1; set<size; set++){
    M[set]=new int[n];
    for(k=0; k<n; k++){
      if(set & (1<<k)){ //on vérifie que k soit dans set, si c'est le cas on calcule C(set,k)
	if(k==set){ //si set est un singleton, on l'initialise à 0
	  M[set][k]=0;
	}
	else{     //sinon on cherche le maximum des C(set\k,m)+d(m,k)
	  tmax=0;
	  for(m=0; m<n; m++){
	    if(k!=m && (set & (1<<m))){ // vérification que m est dans set et est distinct de k
	      mk=(M[set-(1<<k)][m]+T[m][k]);
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
  tmax=0,set=size-1;
  int pos=-1, nextpos; 
  int* MaxPath=new int[n];
  for(k=0; k<n;k++){
    if(tmax<M[set][k]){
      tmax=M[set][k];
      pos=k;
    }
  }
  MaxPath[n-1]=pos;
  for(i=n-2; i>=0; i--){
    set-=1<<pos;
    for(m=0;m<n; m++){
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
  for(k=0;k<size;k++){
    delete[] M[k];
    }
  delete[] M;
  return MaxPath;
}




//anciennes versions de TSP_DP avec une moins bonne efficacité


/* 
// Version avec Max(a,b)


int max(int a, int b){
  return a>b?a:b;
}
int TSP_DP1(vector<vector<int> > &T, int n){
  int size=1<<n, k, m, set, tmax;
  vector<vector<int> > M(size,vector<int>(n));
  for(set=1; set<size; set++){
    for(k=0; k<n; k++){
      if(set & (1<<k)){ //on vérifie que k soit dans set, si c'est le cas on calcule C(set,k)
	if(k==set){ //si set est un singleton, on l'initialise à 0
	  M[set][k]=0;
	}
	else{
	  for(m=0; m<n; m++){
	    if(m!=k && (set & (1<<m))){ // vérification que m est dans set et soit distinct de k
	      M[set][k]=max(M[set][k],(M[set-(1<<k)][m]+T[m][k]));
	       }
	  }
	}
      }
    }
    
  }
  tmax=0;
  for(k=0; k<n;k++){
    tmax=max(tmax,M[size-1][k]);
   }
  return tmax;
}
     


//version sans sauvegarde du max avant le if

int TSP_DP2(vector<vector<int> > &T, int n){
  int size=1<<n, k, m, set, tmax;
  vector<vector<int> > M(size,vector<int>(n));
  for(set=1; set<size; set++){
    for(k=0; k<n; k++){
      if(set & (1<<k)){ //on vérifie que k soit dans set, si c'est le cas on calcule C(set,k)
	if(k==set){ //si set est un singleton, on l'initialise à 0
	  M[set][k]=0;
	}
	else{
	  tmax=0;
	  for(m=0; m<n; m++){
	    if(m!=k && (set & (1<<m))){ // vérification que m est dans set et soit distinct de k
	      if(tmax<(M[set-(1<<k)][m]+T[m][k]))
		tmax=M[set-(1<<k)][m]+T[m][k];
	    }
	  }
	  M[set][k]=tmax;
	}
      }
    }
    
  }
  tmax=0;
  for(k=0; k<n;k++){
    tmax=max(tmax,M[size-1][k]);
   }
  return tmax;
  } 



//version avec déclaration pendant 

int TSP_DP2(vector<vector<int> > &T, int n){ 
  int size=1<<n;
  vector<vector<int> > M(size,vector<int>(n));
  for(int set=1; set<size; set++){
    for(int k=0; k<n; k++){
      if(set & (1<<k)){ //on vérifie que k soit dans set, si c'est le cas on calcule C(set,k)
	if(k==set){ //si set est un singleton, on l'initialise à 0
	  M[set][k]=0;
	}
	else{
	  int tmax=0;
	  for(int m=0; m<n; m++){
	    if(m!=k && (set & (1<<m))){ // vérification que m est dans set et soit distinct de k
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
  int tmax=0;
  for(int k=0; k<n;k++){
    tmax=max(tmax,M[size-1][k]);
   }
  return tmax;
}


//version avec unsigned int

int TSP_DP3(vector<vector<int> > &T, int n){
  unsigned int size=1<<n, k, m, set, tmax, mk;
  vector<vector<unsigned int> > M(size,vector<unsigned int>(n));
  for(set=1; set<size; set++){
    for(k=0; k<n; k++){
      if(set & (1<<k)){ //on vérifie que k soit dans set, si c'est le cas on calcule C(set,k)
	if(k==set){ //si set est un singleton, on l'initialise à 0
	  M[set][k]=0;
	}
	else{
	  tmax=0;
	  for(m=0; m<n; m++){
	    if(m!=k && (set & (1<<m))){ // vérification que m est dans set et distinct de k
	      mk=(M[set-(1<<k)][m]+T[m][k]);
	      if(tmax<mk)
		tmax=mk;
	    }
	  }
	  M[set][k]=tmax;
	}
      }
    }
    
  }
  tmax=0;
  for(k=0; k<n;k++){
     if(tmax<M[size-1][k]){
       tmax=M[size-1][k];
    }
   }
  cout<<endl;
  return tmax;


//dernière version utilisant les vector pour M

int TSP_DP3(vector<vector<int> > &T, int n){
  int size=1<<n, k, m, set, tmax, mk;
  vector<vector<int> > M(size,vector<int>(n));
  for(set=1; set<size; set++){
    for(k=0; k<n; k++){
      if(set & (1<<k)){ //on vérifie que k soit dans set, si c'est le cas on calcule C(set,k)
	if(k==set){ //si set est un singleton, on l'initialise à 0
	  M[set][k]=0;
	}
	else{
	  tmax=0;
	  for(m=0; m<n; m++){
	    if(set & (1<<m)){ // vérification que m est dans set et distinct de k
	      mk=(M[set-(1<<k)][m]+T[m][k]);
	      if(tmax<mk)
		tmax=mk;
	    }
	  }
	  M[set][k]=tmax;
	}
      }
    }
    
  }
  tmax=0;
  for(k=0; k<n;k++){
     if(tmax<M[size-1][k]){
       tmax=M[size-1][k];
    }
   }
  cout<<endl;
  return tmax;
}
}
*/

