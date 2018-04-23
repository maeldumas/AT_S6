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


int TSP_DP1_int(int** &T, int n){
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
  int tmax=-1;
  for(int k=0; k<n;k++){
    if(tmax<M[size-1][k]){
      tmax=M[size-1][k];
    }
  }
  for(int k=0;k<size;k++){
    delete[] M[k];
  }
  delete[] M;
  return tmax;
}
      

int* TSP_DP1(int** &T, int n){ 
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



void list_subsets_bysize(int ens, int nextelement, vector<vector<int> > &T, int n, int size_set){
  if(nextelement<n){
    int enst=ens+(1<<nextelement);
    T[size_set].push_back(enst);
    list_subsets_bysize(enst, nextelement+1,T,n,size_set+1);
    list_subsets_bysize(ens, nextelement+1,T,n,size_set);
  }
}

int TSP_DP2_int(int** &T, int n){
  int size=1<<n;
  int** M=new int*[size];
  vector<vector<int> > subsets(n);
   list_subsets_bysize(0,0,subsets,n,0);
  
  for(int i=0; i<n; i++){
    int set=subsets[0][i];
    M[set]=new int;
    M[set][0]=0;
  }
  for(int i=1; i<n; i++){ //pour toutes les tailles i  d'ensemble allant de 2 à n
    for(int set=0; set<subsets[i].size();set++){ // pour tous les ensembles de taille i
      M[subsets[i][set]]=new int[i+1];  //on créé une liste de paire de la taille de l'ensemble
      int cpt=0, k=0;
      while(cpt<i+1){ 
	int tset=subsets[i][set];
	if(tset & (1<<k)){ // on vérifie que k soit dans l'ensemble
	  int tsubset=tset-(1<<k), tmax=-1, cptsub=0, m=0;
	  while(cptsub<i){ // pour chaque élément m du subset privé de k 
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
    for(int set=0; set<subsets[i-1].size();set++){ // pour tous les ensembles de taille i-1
      delete[] M[subsets[i-1][set]];
    }
  
  }

   int tmax=-1;
  for(int k=0; k<n;k++){
    if(tmax<M[size-1][k]){
      tmax=M[size-1][k];
    }
  }
  
   delete[] M[size-1];
  delete[] M;
  
  return tmax;
}


int* TSP_DP2(int** &T, int n){
  int size=1<<n;
  int** M=new int*[size];
  vector<vector<int> > subsets(n);
  list_subsets_bysize(0,0,subsets,n,0);
  
  for(int i=0; i<n; i++){
    int set=subsets[0][i];
    M[set]=new int;
    M[set][0]=0;
  }
  
  for(int i=1; i<n; i++){ //pour toutes les tailles i  d'ensemble allant de 2 à n
    for(int set=0; set<subsets[i].size();set++){ // pour tous les ensembles de taille i
      M[subsets[i][set]]=new int[i+1];  //on créé une liste de paire de la taille de l'ensemble
      int cpt=0, k=0;
      while(cpt<i+1){ 
	int tset=subsets[i][set];
	if(tset & (1<<k)){ // on vérifie que k soit dans l'ensemble
	  int tsubset=tset-(1<<k), tmax=-1, cptsub=0, m=0;
	  while(cptsub<i){ // pour chaque élément m du subset privé de k 
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

  //backtracking

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
    int cpt=0, k=0;  //k : nom de l'elt, cpt : position dans le sous-ensemble de l'elt
    while(cpt<i+1){
      if(set & (1<<k)){ // si k est dans le set
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



//nouvelle implémentation avec paire

struct paire{
  short int elt;
  int val;
};


int TSP_DP3(int** &T, int n){
  int size=1<<n;
  paire** M=new paire*[size];
  vector<vector<int> > subsets(n);
  list_subsets_bysize(0,0,subsets,n,0);
  for(int i=0; i<n; i++){
    subsets[i].shrink_to_fit();
  }
  for(int i=0; i<n; i++){
    int set=subsets[0][i];
    M[set]=new paire;
    M[set][0].elt=i;
    M[set][0].val=0;
  }
  for(int i=1; i<n; i++){ //pour toutes les tailles i  d'ensemble allant de 2 à n
    for(int set=0; set<subsets[i].size();set++){ // pour tous les ensembles de taille i
      M[subsets[i][set]]=new paire[i+1];  //on créé une liste de paire de la taille de l'ensemble
      int cpt=0;
      int k=0; // pour tous les éléments k de l'ensemble
      while(cpt<i+1){ // si pb remplacer par une boucle for
	int tset=subsets[i][set];
	if(tset & (1<<k)){ // on vérifie que k soit dans l'ensemble
	  M[tset][cpt].elt=k;
	  int tsubset=tset-(1<<k);
	  int tmax=-1;
	  for(int m=0; m<i; m++){ // pour chaque élément m du subset privé de k
	    int lastpos=M[tsubset][m].elt;
	    int valpath=M[tsubset][m].val;
	    int mk=valpath+T[lastpos][k];
	    if(tmax<mk){
	      tmax=mk;
	    }
	    M[tset][cpt].val=tmax;
	  }
	  cpt++;
	}
	k++;
      }
    }
    for(int set=0; set<subsets[i-1].size();set++){ // pour tous les ensembles de taille i-1
      delete[] M[subsets[i-1][set]];
    }
  }

  //backtracking
  int tmax=-1;
  for(int k=0; k<n;k++){
    if(tmax<M[size-1][k].val){
      tmax=M[size-1][k].val;
    }
  }

  delete[] M[size-1];
  delete[] M;

  
  return tmax;
}

int* TSP_DP4(int** &T, int n){
  int size=1<<n;
  paire** M=new paire*[size];
  vector<vector<int> > subsets(n);
  list_subsets_bysize(0,0,subsets,n,0);
  for(int i=0; i<n; i++){
    subsets[i].shrink_to_fit();
  }
  for(int i=0; i<n; i++){
    int set=subsets[0][i];
    M[set]=new paire;
    M[set][0].elt=i;
    M[set][0].val=0;
  }
  for(int i=1; i<n; i++){ //pour toutes les tailles i  d'ensemble allant de 2 à n
    for(int set=0; set<subsets[i].size();set++){ // pour tous les ensembles de taille i
      M[subsets[i][set]]=new paire[i+1];  //on créé une liste de paire de la taille de l'ensemble
      int cpt=0;
      int k=0; // pour tous les éléments k de l'ensemble
      while(cpt<i+1){ // si pb remplacer par une boucle for
	int tset=subsets[i][set];
	if(tset & (1<<k)){ // on vérifie que k soit dans l'ensemble
	  M[tset][cpt].elt=k;
	  int tsubset=tset-(1<<k);
	  int tmax=-1;
	  for(int m=0; m<i; m++){ // pour chaque élément m du subset privé de k
	    int lastpos=M[tsubset][m].elt;
	    int valpath=M[tsubset][m].val;
	    int mk=valpath+T[lastpos][k];
	    if(tmax<mk){
	      tmax=mk;
	    }
	    M[tset][cpt].val=tmax;
	  }
	  cpt++;
	}
	k++;
      }
    }
  }
  //backtracking
  int tmax=-1;
  int set=size-1;
  int pos=-1, nextpos; 
  int* MaxPath=new int[n];
  for(int k=0; k<n;k++){
    if(tmax<M[set][k].val){
      tmax=M[set][k].val;
      pos=M[set][k].elt;
    }
  }
  MaxPath[n-1]=pos;
  for(int i=n-2; i>=0; i--){
    set-=1<<pos;
    for(int m=0;m<i+1; m++){
      if(tmax==M[set][m].val+T[M[set][m].elt][pos]){
	nextpos=M[set][m].elt;
      }
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







int TSP_DP1(int** &T, int n){
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
  tmax=-1;
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
  tmax=-1,set=size-1;
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

*/

