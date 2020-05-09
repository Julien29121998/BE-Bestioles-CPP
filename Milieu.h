#ifndef _MILIEU_H_
#define _MILIEU_H_


#include "UImg.h"
#include "DBestiole.h"

#include <iostream>
#include <vector>

using namespace std;


class Milieu : public UImg
{

private :
   static const T          white[];

   int                     width, height;
   std::vector<DBestiole*>   listeBestioles;

public :
   Milieu( int _width, int _height );
   ~Milieu();

   int getWidth() const { return width; };
   int getHeight() const { return height; };

   void step();

   void addMember(DBestiole* b ) { listeBestioles.push_back(b); listeBestioles.back()->initCoords(width, height); }
   int nbVoisins( const DBestiole* b );

};


#endif
