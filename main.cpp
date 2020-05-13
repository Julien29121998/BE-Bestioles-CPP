#include "Aquarium.h"
#include "Milieu.h"
#include "DBestiole.h"
#include "Bestiole.h"
#include "Membre.h"
#include "Camouflages.h"
#include "Nageoire.h"
#include "Carapace.h"
#include "Capteur.h"
#include "Oreilles.h"

#include <iostream>

using namespace std;


int main()
{
   Bparams_t params;
   Aquarium       ecosysteme( 640, 480, 30 );

   memset(&params,0,sizeof(params));
   ecosysteme.getMilieu().Introduire(8,params);

   memset(&params,0,sizeof(params));
   Camop_t ct;
   Nagp_t nt;
   Carapp_t cpt;
   cpt.eta = 2.;
   cpt.omega = 2.8;
   ct.phi=0.2;
   nt.nu=2.4;
   params.camo=&ct;
   params.nag=&nt;
   params.cara=&cpt;
   ecosysteme.getMilieu().Introduire(8,params);

   memset(&params,0,sizeof(params));
   Orp_t orpt;
   orpt.delta=8.0;
   orpt.gamma=0.4;
   cpt.eta = 1.1;
   cpt.omega = 1.6;
   params.cara=&cpt;
   params.orei=&orpt;
   ecosysteme.getMilieu().Introduire(8,params);

   ecosysteme.run();


   return 0;

}
