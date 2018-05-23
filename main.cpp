#include <vector>
#include <string>
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <fstream>
#include <iomanip>


using namespace std;


void run();
void test_u();

int main(int argc, char** argv){
  srand(time(NULL));
  run();
  return 0;
}





void test_SSP(string* &, int, bool);
string* create_F(int, int);
void affichage_F(string*&, int);

void afficheMatrice(int**, int);
void overlap_graph(string*&, int&, int**&);
int* TSP_naif(int**&, int);
string SSP(int**&,int*&, string*&, int);
int SSP_int(int**&,int*&, string*&, int);

int* TSP_DP_v1(int**&, int);
int* TSP_DP_v2(int**&, int);
int TSP_DP_vsb(int**&, int);



void run(){
  int opt,n;
  string tabopt[4]={"0 - Exécution avec un exemple prédéfini",
		    "1 - Exécution avec saisie des mots",
		    "2 - Exécution avec un exemple aléatoire",
		    "3 - Exécution avec série croissante de mots aléatoires"};
  cout<<"Veuillez saisir le mode d'exécution du programme :"<<endl;
  for(int i=0; i<4; i++){
    cout<<tabopt[i]<<endl;
  }
  do{
    cout<<"Saisie : ";
    cin>>opt;}
  while(opt<0 || opt>4);
  cout<<endl;
  switch(opt){

    
  case 0 :{
    n=5;
    string* F=new string[n];
    F[0]="ACCTGAG";
    F[1]="CAAT";
    F[2]="TGCATTGC";
    F[3]="GCAGACC";
    F[4]="AGCAAT";
    affichage_F(F,n);
    test_SSP(F,n,true);
    delete[] F;
    break;
  }

    
  case 1 :{
    cout<<"Entrez le nombre de mots que vous souhaitez : ";
    cin>>n;
    string* F=new string[n];
    string S;
    cout<<"Entrez les "<<n<<" chaînes de caractères : "<<endl;
    for(int i=0; i<n; i++){
      cin>>S;
      F[i]=S;
    }
    test_SSP(F,n,true);
    delete[] F;
    break;
  }

    
  case 2 :{
    int t;
    cout<<"Entrez le nombre de mots que vous souhaitez : ";
    cin>>n;
    cout<<"Entrez la taille des mots : ";
    cin>>t;

    string* F;
    F=create_F(n,t);
    affichage_F(F,n);
    test_SSP(F,n,true);
    delete[] F;   
    break;
  }

    
  case 3 :{
    int t;
    cout<<"Entrez jusqu'à combien de mots vous souhaitez aller : ";
    cin>>n;
    cout<<"Entrez la taille des mots : ";
    cin>>t;
    for(int i=1; i<=n; i++){
      string* F;
     F=create_F(i,t);
      test_SSP(F,i,false);
      delete[] F;
      cout<<endl;
    }
    break;
  }
  }
}

void test_SSP(string* &F, int n, bool affichage){
  clock_t t,w;
 
  
  //création du graphe de chevauchement T à partir de F :
  int** T=new int*[n];
  for(int i=0; i<n; i++)
    T[i]=new int[n];
  t=clock();
  overlap_graph(F,n,T);
  w=clock()-t;
  if(affichage){
    cout<<"fin de la création du graphe de chevauchement, elle a durée : "<<((float)w)/CLOCKS_PER_SEC<<"s"<<endl;
    afficheMatrice(T,n);
  }
  cout<<"Le graphe de chevauchement est de taille : "<<n<<endl;
  if(affichage)cout<<endl;
 


  
  //Exécution du TSP naïf sur la grahe T
  if(n<12){
    int* TSP;
    t=clock();
    TSP=TSP_naif(T,n);
    w=clock()-t;
    cout<<"fin de l'exécution du TSP naïf, elle a durée : "<<((float)w)/CLOCKS_PER_SEC<<"s"<<endl;
    if(affichage) cout<<"SSP avec TSP naïf : "<<endl<<SSP(T,TSP,F,n)<<endl<<endl;;
    delete[] TSP;
  }
  else{
    cout<<"Le TSP naïf n'a pas été exécuté car le graphe est de taile > 11, le temps d'exécution dépasse 1 min"<<endl;
  }

  
  //Exécution du TSP_DP_v2
  if(n<25){
    int* TSP;
    t=clock();
    TSP=TSP_DP_v2(T,n);
    w=clock()-t;
    cout<<"fin de l'exécution du TSP_DP_v2, elle a durée : "<<((float)w)/CLOCKS_PER_SEC<<"s"<<endl;
    if(affichage)
      cout<<"SSP avec TSP_DP_v2 : "<<endl<<SSP(T,TSP,F,n)<<endl<<endl;
    delete[] TSP;
      }
  else
    {
      cout<<"Le TSP_DP_v2 n'a pas été exécuté car le graphe est de taile > 24, l'espace mémoire utilisé est trop grand"<<endl;
    }

  //Exécution du TSP_DP_vsb
  if(n<26){
    t=clock();
    int res=TSP_DP_vsb(T,n);
    w=clock()-t;
    cout<<"fin de l'exécution du TSP_DP_vsb, elle a durée : "<<((float)w)/CLOCKS_PER_SEC<<"s"<<endl;
    if(affichage)
      cout<<"Poids du chemin avec TSP_DP_vsb : "<<res<<endl;
    else
      cout<<endl;
  }
  else
    {
      cout<<"Le TSP_DP_vsb n'a pas été exécuté car le graphe est de taile > 25, l'espace mémoire utilisé est trop grand"<<endl;
    }

  
  for(int i=0;i<n;i++)
    delete[] T[i];
  delete[] T;
}

string* create_F(int n, int t){
 string* F=new string[n];
 string E[3]={"A","B","C"};
 int k;
 string S;
 for(int i=0; i<n; i++){
    S="";
    for(int j=0;j<t; j++){
      k=rand()%3;
      S+=E[k];
      }
    F[i]=S;
  }
 return F;
}


void affichage_F(string*& F, int n){
  cout<<"La liste des mots est : "<<endl;
  for(int i=0; i<n; i++){
    cout<<F[i]<<endl;
  }
  cout<<endl;
}



void test_u(){
  int n,t;
  cout<<"Entrez le nombre de mots que vous souhaitez : ";
  cin>>n;
  cout<<"Entrez la taille des mots : ";
  cin>>t;

  string* F;
  F=create_F(n,t);
  affichage_F(F,n);

  clock_t x,w;
   
  //création du graphe de chevauchement T à partir de F :
  int** T=new int*[n];
  for(int i=0; i<n; i++)
    T[i]=new int[n];
  x=clock();
  overlap_graph(F,n,T);
  w=clock()-x;
  cout<<"fin de la création du graphe de chevauchement, elle a durée : "<<((float)w)/CLOCKS_PER_SEC<<"s"<<endl;
  afficheMatrice(T,n);
  cout<<"Le graphe de chevauchement est de taille : "<<n<<endl;
  cout<<endl;

  x=clock();
  int* TSP=TSP_DP_v2(T,n);
  w=clock()-x;
  cout<<"fin de l'exécution du TSP_DP_v2, elle a durée : "<<((float)w)/CLOCKS_PER_SEC<<"s"<<endl;
  cout<<"SSP avec TSP_DP_v2 : "<<endl<<SSP(T,TSP,F,n)<<endl<<endl;


  delete[] TSP;
  delete[] F;
   for(int i=0;i<n;i++)
    delete[] T[i];
  delete[] T;
}










