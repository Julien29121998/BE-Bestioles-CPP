#ifndef _MILIEU_H_
#define _MILIEU_H_


#include "UImg.h"
#include "DBestiole.h"
#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Factory;
class IComportement;

class Milieu : public UImg
{

private :
   static const T            white[];

   int                       width, height;
   int                       target_pop;
   int                       timer;

   std::vector<DBestiole*>   listeBestioles;

public :
   std::vector<IComportement*> Comportements_Disponibles;
   IComportement*              Comportement_par_defaut;
   std::vector<Factory>        listeFactories;

   Milieu( int _width, int _height, int target_population );
   ~Milieu();

   int getWidth() const { return width; };
   int getHeight() const { return height; };

   void step(std::vector<Factory> nf);

   int nbVoisins( const DBestiole* b );
   std::vector<DBestiole*> QuiVoisJe( const DBestiole* b);
   void kill(int id);
   void introduire();
   void handleCollisions(DBestiole* b);
   void describeMe() const;
   int Count() const;
   std::map<std::string,int> contenu() const;
};


#endif
