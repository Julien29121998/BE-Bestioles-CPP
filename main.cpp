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
   Camop_t ct;
   Carapp_t cpt;
   cpt.eta = 2.;
   cpt.omega = 2.8;
   ct.phi=0.8;
   params.camo=&ct;
   params.cara=&cpt;
   ecosysteme.getMilieu().Introduire(9,params);

   memset(&params,0,sizeof(params));
   Nagp_t ngt;
   Orp_t opt;
   opt.delta=18.5;
   opt.gamma=0.9;
   ngt.nu = 3.1;
   ct.phi=0.2;
   params.camo=&ct;
   params.nag=&ngt;
   params.orei=&opt;
   ecosysteme.getMilieu().Introduire(9,params);

   memset(&params,0,sizeof(params));
   Yeuxp_t ypt;
   ypt.delta=48.6;
   ypt.gamma=0.4;
   ypt.alpha=0.78;
   params.yeux=&ypt;
   ecosysteme.getMilieu().Introduire(6,params);

   memset(&params,0,sizeof(params));
   ypt.delta=31.;
   ypt.gamma=0.4;
   ypt.alpha=0.66;
   params.yeux=&ypt;
   opt.delta=16.9;
   opt.gamma=0.88;
   params.orei=&opt;
   ecosysteme.getMilieu().Introduire(7,params);

   ecosysteme.run();


   return 0;

}
