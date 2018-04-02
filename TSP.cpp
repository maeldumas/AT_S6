#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

vector<int> TSP_naif(vector<vector<int> > &T, int n){
  vector<int> permutation(n),permutationMax(n);
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
 
  /*
    cout << "The "<<n<<"! possible permutations with "<<n<<" elements:\n";
    do {
    for(i=0; i<n; i++)
    cout << permutation[i] << ' ';
    cout << '\n';
    } while ( next_permutation(permutation.begin(),permutation.end()) );

    cout << "After loop: ";
    for(i=0; i<n; i++)
    cout << permutation[i] << ' ';
    cout << '\n';
   cout << "After loop: ";
    for(i=0; i<n; i++)
    cout << permutationMax[i] << ' ';
    cout << '\n';*/
  return permutationMax;
}
	      
   
string SSP(vector<vector<int> > &T,vector<int> &TSP, vector<string> &F, int n){
  string S=F[TSP[0]];
  for(int i=1;i<n;i++){
    S+=F[TSP[i]].substr(T[TSP[i-1]][TSP[i]]);
  }
  return S;
}

 
