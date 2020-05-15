#ifndef _MILIEU_H_
#define _MILIEU_H_


#include "UImg.h"
#include "DBestiole.h"
#include <iostream>
#include <vector>

using namespace std;

class Factory;

class Milieu : public UImg
{

private :
   static const T            white[];

   int                       width, height;

   std::vector<DBestiole*>   listeBestioles;

public :
   std::vector<Factory>      listeFactories;
   Milieu( int _width, int _height );
   ~Milieu();

   int getWidth() const { return width; };
   int getHeight() const { return height; };

   void step();

   int nbVoisins( const DBestiole* b );
   void kill(int id);
   void introduire(int combien);

};


#endif
