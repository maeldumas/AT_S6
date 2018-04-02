#include <vector>
#include <string>
#include <iostream>

using namespace std;

void afficheMatrice(vector<vector<int> >, int);
void afficheMatrice_dot(vector<vector<int> >, int, vector<string>, string);
int overlap(string, string);
int overlap_naif(string, string);
void overlap_graph_naif(vector<string>&, int&, vector<vector<int> >&);
void overlap_graph(vector<string>&, int&, vector<vector<int> >&);
vector<int> TSP_naif(vector<vector<int> >&, int);
string SSP(vector<vector<int> >&,vector<int>&, vector<string>&, int);


int main(int argc, char** argv){
  /*string s1, s2;
    cout<<"Donnez deux chaines de caractères"<<endl;
    cin>>s1>>s2;
    cout<<overlap(s1,s2)<<endl;*/
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
  return 0;
}
