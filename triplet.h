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
  triplet(const triplet &t);


  int get_deb() const;
  int get_fin() const;
  int get_poids() const;


  void set_deb(int a);
  void set_fin(int b);
  void set_poids(int c);

triplet& operator= (const triplet &t);
bool operator== (const triplet &t);

void print();

};

#endif
