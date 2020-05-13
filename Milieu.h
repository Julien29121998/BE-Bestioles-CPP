#ifndef _MILIEU_H_
#define _MILIEU_H_


#include "UImg.h"
#include "DBestiole.h"
#include "Bestiole.h"
#include "Camouflages.h"
#include "Nageoire.h"
#include "Carapace.h"
#include "Oreilles.h"

#include <iostream>
#include <vector>

using namespace std;

typedef struct CamoParams{
   double phi;
} Camop_t;
typedef struct NageoParams{
   double nu;
} Nagp_t;
typedef struct CaraParams{
   double omega;
   double eta;
} Carapp_t;
typedef struct OreParams{
   double delta;
   double gamma;
} Orp_t;

typedef struct BestiolesParams{
   Camop_t* camo;  
   Nagp_t* nag; 
   Carapp_t* cara;
   Orp_t* orei;
} Bparams_t;

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
   void kill(int id);
   void Introduire(int combien,Bparams_t params);

};


#endif
