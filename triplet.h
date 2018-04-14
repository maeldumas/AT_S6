#ifndef __TRIPLET_H
#define __TRIPLET_H

class triplet{
  private:
  int deb;
  int fin;
  int poids;

 public:

  triplet();
  triplet(int a, int b, int c);


  int get_deb();
  int get_fin();
  int get_poids();


  void set_deb(int a);
  void set_fin(int b);
  void set_poids(int c);

triplet& operator= (triplet &t);
bool egal(triplet t);

void print();

};

#endif
