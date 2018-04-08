#include <vector>
#include <string>
#include <iostream>
#include <time.h>
#include <cstdlib>


using namespace std;

void afficheMatrice(vector<vector<int> >, int);
void afficheMatrice_dot(vector<vector<int> >, int, vector<string>, string);
int overlap(string, string);
int overlap_naif(string, string);
void overlap_graph_naif(vector<string>&, int&, vector<vector<int> >&);
void overlap_graph(vector<string>&, int&, vector<vector<int> >&);
vector<int> TSP_naif(vector<vector<int> >&, int);
string SSP(vector<vector<int> >&,vector<int>&, vector<string>&, int);
int SSP_int(vector<vector<int> >&,vector<int>&, vector<string>&, int);
int TSP_DP1(vector<vector<int> >&, int);
vector<int> TSP_DP2(vector<vector<int> >&, int);
void test_1();
void test_2();
void test_rpz();

int main(int argc, char** argv){
  /*string s1, s2;
    cout<<"Donnez deux chaines de caractères"<<endl;
    cin>>s1>>s2;
    cout<<overlap(s1,s2)<<endl;*/
  //test_1();
  srand(time(NULL));
  test_2();
  //test_rpz();
  return 0;
}

void test_1(){
    vector<string> F;
  F.push_back("ACCTGAG");
  F.push_back("CAAT");
  F.push_back("TGCATTGC");
  F.push_back("GCAGACC");
  F.push_back("CAAT");
  F.push_back("AGCAAT");
  F.push_back("CAAT");
  
  int n=F.size();
  vector<vector<int> > T(n);
  for(int i=0; i<n; i++)
    T[i]=vector<int>(n);
  overlap_graph(F,n,T);
  afficheMatrice(T,n);
  //afficheMatrice_dot(T,n,F,"graph.dot");
  vector<int> TSP;
  string S;
   TSP=TSP_naif(T,n);
  S=SSP(T,TSP,F,n);
  cout<<S<<endl;
  cout<<"taille max : "<<SSP_int(T,TSP,F,n)<<endl;
  cout<<"taille max avec TSP_DP1 :"<<TSP_DP1(T,n)<<endl;
}



void test_2(){
  int n, inf, sup, tn, k, i ,j;
  string S;
  clock_t t,w;
  cout<<"entrez le nombre de chaines de caractères que vous souhaitez :"<<endl;
  cin>>n;
  cout<<"entrez la taille minimale de la chaine de caractère :"<<endl;
  cin>>inf;
  cout<<"entrez la taille maximale de la chaine de caractère :"<<endl;
  cin>>sup;
  vector<string> F(n);
  t=clock();
  for(i=0; i<n; i++){
    tn=(rand()%(sup-inf+1))+inf;
    S="";
    for(j=0;j<tn; j++){
      k=rand()%4;
      switch(k){
      case 0 :{S+='A'; break;}
      case 1 :{S+='C'; break;}
      case 2 :{S+='G'; break;}
      case 3 :{S+='T'; break;}
      }
    }
    F[i]=S;
  }
  w=clock()-t;
  cout<<"fin de la création de la liste de chaines de caractères, elle a durée : "<<((float)w)/CLOCKS_PER_SEC<<"s"<<"\n";
  cout<<"Les chaines de caractères générées sont les suivantes :"<<endl;
  for(i=0; i<n; i++)
  cout<<F[i]<<' '<<endl;
  
  //création du graphe de chevauchement T à partir de F :
  vector<vector<int> > T(n);
  for(int i=0; i<n; i++)
    T[i]=vector<int>(n);
  t=clock();
    overlap_graph(F,n,T);
  w=clock()-t;
  cout<<"fin de la création du graphe de chevauchement, elle a durée : "<<((float)w)/CLOCKS_PER_SEC<<"s"<<"\n";
  cout<<"Le graphe de chevauchement est de taille : "<<n<<endl;
  afficheMatrice(T,n);
  // afficheMatrice_dot(T,n,F,"graph.dot");

  vector<int> TSP;
  
  //Execution du TSP naïf sur la grahe T 
   /*   t=clock();
  TSP=TSP_naif(T,n);
  w=clock()-t;
  cout<<"fin de l'éxécution du TSP naïf, elle a durée : "<<((float)w)/CLOCKS_PER_SEC<<"s"<<"\n";
  S=SSP(T,TSP,F,n);
  //cout<<S<<endl;
  */

  //Execution du TSP_DP sans backtracking (taille du plus long chemin seulement)
   /*
  t=clock();
  int z=TSP_DP1(T,n);
  w=clock()-t;
  cout<<"fin de l'éxécution du TSP_DP1, elle a durée : "<<((float)w)/CLOCKS_PER_SEC<<"s"<<"\n";
  */

  //Execution du TSP_DP avec backtracking
  t=clock();
  TSP=TSP_DP2(T,n);
  w=clock()-t;
  cout<<"fin de l'éxécution du TSP_DP2, elle a durée : "<<((float)w)/CLOCKS_PER_SEC<<"s"<<"\n";
  

  //cout<<"SSP avec TSP naïf : "<<endl<<S<<endl;
  cout<<"SSP avec TSP_DP : "<<endl<<SSP(T,TSP,F,n)<<endl;
  //cout<<"taille max : "<<SSP_int(T,TSP,F,n)<<endl;
  // cout<<"taille max avec TSP_DP1 : "<<z<<endl;
}

void iter(int ens, int nextelement, vector<vector<int> > &T, int n, int size_set){
  // cout<<"ens :"<<ens<<", nextelement :"<<nextelement<<", n"<<n<<", size_set :"<<size_set<<endl;
  if(nextelement<n){
    int enst=ens+(1<<nextelement);
    T[size_set].push_back(enst);
    iter(enst, nextelement+1,T,n,size_set+1);
    iter(ens, nextelement+1,T,n,size_set);
  }
}
  


void test_rpz(){
  /* int n,ens=0;
  bool b;
  cout<<"entrez la taille de votre ensemble :"<<endl;
  cin>>n;
  for(int i=0; i<n; i++){
    cout<<i<<" est-il dans votre ensemble ?"<<endl;
    cin>>b;
    ens+=b?1<<i:0;
  }
  for(int i=0; i<n; i++){
    cout<<i<<((ens>>i)&1?"est":"n'est pas")<<" dans votre ensemble"<<endl;
    }*/
  int n;
  cout<<"entrez la taille de votre ensemble :"<<endl;
  cin>>n;
  vector<vector<int> > T(n);
  iter(0,0,T,n,0);
  cout<<"Affichage de tous les sous-ensemble (codé) :"<<endl;
  for(int i=0;i<n;i++){
    for(int j=0; j<T[i].size();j++)
      cout<<T[i][j]<<' ';
    cout<<endl;
  }

}
  
