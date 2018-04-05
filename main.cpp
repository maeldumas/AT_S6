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
void test_1();
void test_2();
void test_rpz();

int main(int argc, char** argv){
  /*string s1, s2;
    cout<<"Donnez deux chaines de caractères"<<endl;
    cin>>s1>>s2;
    cout<<overlap(s1,s2)<<endl;*/
  //test_1();
  //srand(time(NULL));
  // test_2();
  test_rpz();
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

  //Execution du TSP naïf sur la grahe T
  vector<int> TSP;
  t=clock();
  TSP=TSP_naif(T,n);
  w=clock()-t;
  cout<<"fin de l'éxécution du TSP naïf, elle a durée : "<<((float)w)/CLOCKS_PER_SEC<<"s"<<"\n";
  S=SSP(T,TSP,F,n);
  cout<<S<<endl;
}


void test_rpz(){
  int n,ens=0;
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
  }
    
 
}
  
    
