#include "Aquarium.h"
#include "Milieu.h"
#include "DBestiole.h"
#include "Bestiole.h"
#include "Membre.h"
#include "Camouflages.h"
#include "Nageoire.h"

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
   Nagp_t nt;
   ct.phi=0.2;
   nt.nu=0.9;
   params.camo=&ct;
   params.nag=&nt;
   ecosysteme.getMilieu().Introduire(10,params);
   ecosysteme.run();


   return 0;

}
