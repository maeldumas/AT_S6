#include <vector>
#include <string>
#include <iostream>
#include <time.h>
#include <cstdlib>


using namespace std;

void afficheMatrice(int**, int);
void afficheMatrice_dot(int**, int, string*, string);
int overlap(string, string);
int overlap_naif(string, string);
void overlap_graph_naif(string*&, int&, int**&);
void overlap_graph(string*&, int&, int**&);
int* TSP_naif(int**&, int);
string SSP(int**&,int*&, string*&, int);
int SSP_int(int**&,int*&, string*&, int);
int TSP_DP1_int(int**&, int);
int* TSP_DP1(int**&, int);
int TSP_DP2_int(int**&, int);
int* TSP_DP2(int**&, int);
void test_1();
void test_2();
void test_3(int);
void test_4();
void test_rpz();
void test();
void mesure();

int main(int argc, char** argv){
  srand(time(NULL)); 
  /*string s1, s2;
    cout<<"Donnez deux chaines de caractères"<<endl;
    cin>>s1>>s2;
    cout<<overlap(s1,s2)<<endl;*/
  //test_1();
  //test_2();
  //mesure();
  /*
  int n;
  cout<<"Saisissez le nombre d'iteration :"<<endl;
  cin>>n;
  for(int i=0; i<n; i++)
    test_3(i);*/
  //test_rpz();
  test();
  return 0;
}

void test_SSP(string* &, int, bool);
string* create_F(int, int, int);
void affichage_F(string*&, int);

void test(){
  int opt,n;
  string tabopt[4]={"0 - Exécution avec l'exemple de base",
		    "1 - Exécution avec saisie des chaînes de caractères",
		    "2 - Exécution avec exemple aléatoire",
		    "3 - Exécution avec série croissante d'exemples aléatoires"};
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
    n=6;
    string* F=new string[n];
    F[0]="ACCTGAG";
    F[1]="CAAT";
    F[2]="TGCATTGC";
    F[3]="GCAGACC";
    F[4]="CAAT";
    F[5]="AGCAAT";
    affichage_F(F,n);
    test_SSP(F,n,true);
    delete[] F;
    break;
  }

    
  case 1 :{
    cout<<"Entrez le nombre de chaînes de caractères que vous souhaitez : ";
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
    int sup, inf;
    cout<<"Entrez le nombre de chaînes de caractères que vous souhaitez : ";
    cin>>n;
    cout<<"Entrez la taille minimale d'une chaîne de caractères : ";
    cin>>inf;
    cout<<"Entrez la taille maximale d'une la chaîne de caractères : ";
    cin>>sup;
    string* F;
    F=create_F(n,inf,sup);
    affichage_F(F,n);
    test_SSP(F,n,true);
    delete[] F;   
    break;
  }

    
  case 3 :{
    int sup, inf;
    cout<<"Entrez le nombre de chaînes de caractères que vous souhaitez au maximum : ";
    cin>>n;
    cout<<"Entrez la taille minimale d'une chaîne de caractères : ";
    cin>>inf;
    cout<<"Entrez la taille maximale d'une la chaîne de caractères : ";
    cin>>sup;
    for(int i=1; i<=n; i++){
      string* F;
     F=create_F(i,inf,sup);
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

  
  //Exécution du TSP_DP1 avec backtracking
  if(n<25){
    int* TSP;
    t=clock();
    TSP=TSP_DP1(T,n);
    w=clock()-t;
    cout<<"fin de l'exécution du TSP_DP1, elle a durée : "<<((float)w)/CLOCKS_PER_SEC<<"s"<<endl;
    if(affichage)
      cout<<"SSP avec TSP_DP1 : "<<endl<<SSP(T,TSP,F,n)<<endl<<endl;
    delete[] TSP;
      }
  else
    {
      cout<<"Le TSP_DP n'a pas été exécuté car le graphe est de taile > 24, l'espace mémoire utilisé est trop grand"<<endl;
    }

   //Exécution du TSP_DP avec backtracking
  if(n<25){
    int* TSP;
    t=clock();
    TSP=TSP_DP2(T,n);
    w=clock()-t;
    cout<<"fin de l'exécution du TSP_DP2, elle a durée : "<<((float)w)/CLOCKS_PER_SEC<<"s"<<endl;
    if(affichage)
      cout<<"SSP avec TSP_DP2 : "<<endl<<SSP(T,TSP,F,n)<<endl;
    else
      cout<<endl;
    delete[] TSP;
      }
  else
    {
      cout<<"Le TSP_DP2 n'a pas été exécuté car le graphe est de taile > 24, l'espace mémoire utilisé est trop grand"<<endl;
    }

  
  for(int i=0;i<n;i++)
    delete[] T[i];
  delete[] T;
}

string* create_F(int n, int inf, int sup){
 string* F=new string[n];
 string E[3]={"A","B","C"};
 int tn, k;
 string S;
 for(int i=0; i<n; i++){
    tn=(rand()%(sup-inf+1))+inf;
    S="";
    for(int j=0;j<tn; j++){
      k=rand()%3;
      S+=E[k];
      }
    F[i]=S;
  }
 return F;
}


void affichage_F(string*& F, int n){
  cout<<"La liste des chaînes de caractères est : "<<endl;
  for(int i=0; i<n; i++){
    cout<<F[i]<<endl;
  }
  cout<<endl;
}




















void mesure(){
  cout<<"tour de boucle : "<<endl;
  int n;
  clock_t w,t;
  cin>>n;
  float time[25][3];

  for(int i = 0; i<25; i++){
    cout<<"i = "<<i<<endl;
    float a=0,b=0,c=0;
    int ti=i;
    for(int k=0; k<n; k++){
      int* TSP;
      string* F;
      F=create_F(ti,20,20);
      int** T=new int*[ti];
      for(int j=0; j<ti; j++)
	T[j]=new int[ti];
       overlap_graph_naif(F,ti,T);
       if(i<13){
	//TSP naïf
	t=clock();
	TSP=TSP_naif(T,ti);
	w=clock()-t;
	a+=((float)w)/CLOCKS_PER_SEC;
	delete[] TSP;
      }
    
      //TSP_DP1
      t=clock();
      TSP=TSP_DP1(T,ti);
      w=clock()-t;
      b+=((float)w)/CLOCKS_PER_SEC;
      delete[] TSP;
      
      //TSP_DP2
      t=clock();
      TSP=TSP_DP2(T,ti);
      w=clock()-t;
      c+=((float)w)/CLOCKS_PER_SEC;
      delete[] TSP;
       
      delete[] F;
      for(int j=0;j<ti;j++)
	delete[] T[j];
      delete[] T;
    }
    time[i][0]=(float)a/n;
    time[i][1]=(float)b/n;
    time[i][2]=(float)c/n;
  }
  
  for(int i=0; i<25; i++){
    cout<<time[i][0]<<" - "<<time[i][1]<<" - "<<time[i][2]<<endl;
  }
}




void test_1(){
  string* F=new string[7];
  F[0]="ACCTGAG";
  F[1]="CAAT";
  F[2]="TGCATTGC";
  F[3]="GCAGACC";
  F[4]="CAAT";
  F[5]="AGCAAT";
  F[6]="CAAT";
  
  int n=7;
  int** T=new int*[n];
  for(int i=0; i<n; i++)
    T[i]=new int[n];
  overlap_graph(F,n,T);
  afficheMatrice(T,n);
  //afficheMatrice_dot(T,n,F,"graph.dot");
  int* TSP=new int[n];
  string S;
   TSP=TSP_naif(T,n);
  S=SSP(T,TSP,F,n);
  cout<<S<<endl;
  cout<<"taille max : "<<SSP_int(T,TSP,F,n)<<endl;
  cout<<"taille max avec TSP_DP1_int :"<<TSP_DP1_int(T,n)<<endl;
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


  
  string* F;
  t=clock();
  F=create_F(n,inf,sup);
  w=clock()-t;
  cout<<"fin de la création de la liste de chaines de caractères, elle a durée : "<<((float)w)/CLOCKS_PER_SEC<<"s"<<endl;
  cout<<"Les chaines de caractères générées sont les suivantes :"<<endl;
  for(i=0; i<n; i++)
  cout<<F[i]<<' '<<endl;


  
  //création du graphe de chevauchement T à partir de F :
  int** T=new int*[n];
  for(i=0; i<n; i++)
    T[i]=new int[n];
  t=clock();
    overlap_graph(F,n,T);
  w=clock()-t;
  cout<<"fin de la création du graphe de chevauchement, elle a durée : "<<((float)w)/CLOCKS_PER_SEC<<"s"<<endl;
  cout<<"Le graphe de chevauchement est de taille : "<<n<<endl;
  afficheMatrice(T,n);
  // afficheMatrice_dot(T,n,F,"graph.dot");

  /*
  //Exécution du TSP naïf sur la grahe T 
   t=clock();
  TSP=TSP_naif(T,n);
  w=clock()-t;
  cout<<"fin de l'éxécution du TSP naïf, elle a durée : "<<((float)w)/CLOCKS_PER_SEC<<"s"<<endl;
  int wc=SSP_int(T,TSP,F,n);
  cout<<"TSP naïf : "<<wc<<endl;
  */

  
  int opt;
do{
  cout<<"1 - poids du chemin uniquement, 2 - SSP : "<<endl<<"Saisie : ";
    cin>>opt;}
  while(opt<1 || opt>2);


 
//Exécution du TSP_DP sans backtracking (taille du plus long chemin seulement)
 if(opt==1){
   t=clock();
   int z=TSP_DP1_int(T,n);
   w=clock()-t;
   cout<<"fin de l'éxécution du TSP_DP1_int, elle a durée : "<<((float)w)/CLOCKS_PER_SEC<<"s"<<endl;
   cout<<"taille max avec TSP_DP1_int : "<<z<<endl;
  

   //Exécution du TSP_DP2_int sans backtracking (taille du plus long chemin seulement)
   t=clock();
   int wm=TSP_DP2_int(T,n);
   w=clock()-t;
   cout<<"fin de l'éxécution du TSP_DP2_int, elle a durée : "<<((float)w)/CLOCKS_PER_SEC<<"s"<<endl;
   cout<<"taille max avec TSP_DP2_int : "<<wm<<endl;
 }
 else{
  //Exécution du TSP_DP1 avec backtracking
  int* TSP;
  t=clock();
  TSP=TSP_DP1(T,n);
  w=clock()-t;
  cout<<"fin de l'éxécution du TSP_DP1, elle a durée : "<<((float)w)/CLOCKS_PER_SEC<<"s"<<endl;
  cout<<"SSP avec TSP_DP : "<<endl<<SSP(T,TSP,F,n)<<endl;
  delete[] TSP;
  
  
    //Exécution du TSP_DP2 avec backtracking
   t=clock();
  TSP=TSP_DP2(T,n);
  w=clock()-t;
  cout<<"fin de l'éxécution du TSP_DP2, elle a durée : "<<((float)w)/CLOCKS_PER_SEC<<"s"<<endl;
  cout<<"SSP avec TSP_DP : "<<endl<<SSP(T,TSP,F,n)<<endl;
  delete[] TSP;
 }
  delete[] F;
  for(i=0;i<n;i++)
    delete[] T[i];
  delete[] T;
}




void test_3(int n){ int k, i ,j;
  string S;
  clock_t t,w;
  string* F=new string[n];
  t=clock();
  for(i=0; i<n; i++){
    S="";
    for(j=0;j<15; j++){
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
   //création du graphe de chevauchement T à partir de F :
  int** T=new int*[n];
  for(i=0; i<n; i++)
    T[i]=new int[n];
  t=clock();
    overlap_graph(F,n,T);
  w=clock()-t;
  //afficheMatrice(T,n);
  // afficheMatrice_dot(T,n,F,"graph.dot");

  int* TSP;
  /*
  //Exécution du TSP naïf sur la grahe T 
   t=clock();
  TSP=TSP_naif(T,n);
  w=clock()-t;
  cout<<"fin de l'éxécution du TSP naïf, elle a durée : "<<((float)w)/CLOCKS_PER_SEC<<"s"<<endl;
  S=SSP(T,TSP,F,n);
  //cout<<S<<endl;
  */

  //Exécution du TSP_DP sans backtracking (taille du plus long chemin seulement)
   /*
  t=clock();
  int z=TSP_DP1_int(T,n);
  w=clock()-t;
  cout<<"fin de l'éxécution du TSP_DP1_int, elle a durée : "<<((float)w)/CLOCKS_PER_SEC<<"s"<<endl;
  */

  //Exécution du TSP_DP avec backtracking
  t=clock();
  TSP=TSP_DP1(T,n);
  w=clock()-t;
  cout<<"fin de l'éxécution du TSP_DP1 sur un graphe de taille : "<<n<<", elle a durée : "<<((float)w)/CLOCKS_PER_SEC<<"s"<<endl;


  //cout<<"SSP avec TSP naïf : "<<endl<<S<<endl;
  cout<<"SSP avec TSP_DP : "<<endl<<SSP(T,TSP,F,n)<<endl;
  //cout<<"taille max : "<<SSP_int(T,TSP,F,n)<<endl;
  // cout<<"taille max avec TSP_DP1_int : "<<z<<endl;
  delete[] F;
  delete[] TSP;
  for(i=0;i<n;i++)
    delete[] T[i];
  delete[] T;
}


void test_4(){
  int n;
  string S;
  clock_t t,w;
  cout<<"Entrez le nombre de chaînes de caractères que vous souhaitez : "<<endl;
  cin>>n;
  string* F=new string[n];
  cout<<"Entrez les "<<n<<" chaînes de caractères : "<<endl;
  for(int i=0; i<n; i++){
    cin>>S;
    F[i]=S;
  }

  
  int** T=new int*[n];
  for(int i=0; i<n; i++)
    T[i]=new int[n];
  t=clock();
  overlap_graph(F,n,T);
  w=clock()-t;
  afficheMatrice(T,n);
  // afficheMatrice_dot(T,n,F,"graph.dot");

  int* TSP;
  /*
  //Exécution du TSP naïf sur la grahe T 
   t=clock();
  TSP=TSP_naif(T,n);
  w=clock()-t;
  cout<<"fin de l'éxécution du TSP naïf, elle a durée : "<<((float)w)/CLOCKS_PER_SEC<<"s"<<endl;
  S=SSP(T,TSP,F,n);
  //cout<<S<<endl;
  */

  //Exécution du TSP_DP sans backtracking (taille du plus long chemin seulement)
   /*
  t=clock();
  int z=TSP_DP1_int(T,n);
  w=clock()-t;
  cout<<"fin de l'éxécution du TSP_DP1_int, elle a durée : "<<((float)w)/CLOCKS_PER_SEC<<"s"<<endl;
  */

  //Exécution du TSP_DP avec backtracking
  t=clock();
  TSP=TSP_DP1(T,n);
  w=clock()-t;
  cout<<"fin de l'éxécution du TSP_DP1 sur un graphe de taille : "<<n<<", elle a durée : "<<((float)w)/CLOCKS_PER_SEC<<"s"<<endl;


  //cout<<"SSP avec TSP naïf : "<<endl<<S<<endl;
  cout<<"SSP avec TSP_DP : "<<endl<<SSP(T,TSP,F,n)<<endl;
  //cout<<"taille max : "<<SSP_int(T,TSP,F,n)<<endl;
  // cout<<"taille max avec TSP_DP1_int : "<<z<<endl;
  delete[] F;
  delete[] TSP;
  for(int i=0;i<n;i++)
    delete[] T[i];
  delete[] T;
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
  int n,cpt=0;
  cout<<"entrez la taille de votre ensemble :"<<endl;
  cin>>n;
  clock_t t,w;
  t=clock();
  vector<vector<int> > T(n);
  iter(0,0,T,n,0);
  cout<<"Affichage de tous les sous-ensemble (codé) :"<<endl;
  for(int i=0;i<n;i++){
    for(int j=0; j<T[i].size();j++)
      cout<<T[i][j]<<' ';
    cout<<endl;
  }
  cpt+=T[0].size();
  for(int s=0;s<n;s++){
    cout<<"s = "<<s<<", T[s].size() = "<<T[s].size()<<endl;
    cpt+=T[s].size()*(s+1);
    /*
      for(int set=0; set<T[s].size(); set++){
          
      for(int pset=0; pset<T[s-1].size();pset++){ 
      if((T[s][set]&T[s-1][pset])==T[s-1][pset]){
      int k=T[s][set]-T[s-1][pset];
      for(int m=0;m<s-1;m++){
      cpt++;
      cpt--;
      }
      }
      }
      }*/
  }
  cout<<"base = "<<(1<<n)*n<<", opti = "<<cpt;	  
    
  w=clock()-t;
  cout<<"fin du test : "<<n<<", il a duré : "<<((float)w)/CLOCKS_PER_SEC<<"s"<<"\n";

 

}
  
