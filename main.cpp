#include "Aquarium.h"
#include "Milieu.h"
#include "DBestiole.h"
#include "Bestiole.h"
#include "Membre.h"
#include "Camouflages.h"

#include <iostream>

using namespace std;


int main()
{
   Bparams_t params;
   Aquarium       ecosysteme( 640, 480, 30 );

   memset(&params,0,sizeof(params));
   ecosysteme.getMilieu().Introduire(10,params);

   memset(&params,0,sizeof(params));
   Camop_t ct;
   ct.phi=0.2;
   params.camo=&ct;
   ecosysteme.getMilieu().Introduire(10,params);
   ecosysteme.run();


   return 0;

}
