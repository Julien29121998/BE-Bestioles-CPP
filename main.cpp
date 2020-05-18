#include "Aquarium.h"
#include "Milieu.h"
#include "Factory.h"
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
   Aquarium       ecosysteme( 60, 800, 600, 30 );

  /** Param_Dict paramsf1;
   CamoParams cpm1;
   CaraParams kpm1;
   NageoParams npm1;
   OreParams opm1;
   YeuxParams ypm1;
   ComportParams compm1;
   kpm1.eta = 2.6;
   kpm1.omega = 3.8;
   cpm1.phi=0.1;
   opm1.delta=26.5;
   opm1.gamma=0.3;
   compm1.Comportement=COMP_PEUREUSE;
   opm1.Add(paramsf1);
   kpm1.Add(paramsf1);
   cpm1.Add(paramsf1);
   compm1.Add(paramsf1);
   Factory fact = Factory(paramsf1,0.8);
   ecosysteme.getMilieu().listeFactories.push_back(fact);

   Param_Dict paramsf2;
   CamoParams cpm2;
   CaraParams kpm2;
   NageoParams npm2;
   OreParams opm2;
   YeuxParams ypm2;
   ComportParams compm2;
   opm2.delta=18.5;
   opm2.gamma=0.9;
   npm2.nu = 2.6;
   cpm2.phi=0.2;
   compm2.Comportement=COMP_PEUREUSE;
   opm2.Add(paramsf2);
   npm2.Add(paramsf2);
   cpm2.Add(paramsf2);
   compm2.Add(paramsf2);
   fact = Factory(paramsf2,0.2);
   ecosysteme.getMilieu().listeFactories.push_back(fact);
**/
   Param_Dict paramsf3;
   CamoParams cpm3;
   CaraParams kpm3;
   NageoParams npm3;
   OreParams opm3;
   YeuxParams ypm3;
   ComportParams compm3;
   ypm3.delta=48.6;
   ypm3.gamma=0.4;
   ypm3.alpha=0.78;
   compm3.Comportement=COMP_GREGAIRE;
   ypm3.Add(paramsf3);
   compm3.Add(paramsf3);
   Factory fact = Factory(paramsf3,0.8);
   ecosysteme.getMilieu().listeFactories.push_back(fact);

   Param_Dict paramsf4;
   CamoParams cpm4;
   CaraParams kpm4;
   NageoParams npm4;
   OreParams opm4;
   YeuxParams ypm4;
   ComportParams compm4;
   ypm4.delta=31.;
   ypm4.gamma=0.4;
   ypm4.alpha=0.66;
   opm4.delta=16.9;
   opm4.gamma=0.88;
   npm4.nu=1.8;
   compm4.Comportement=COMP_KAMIKAZE;
   ypm4.Add(paramsf4);
   opm4.Add(paramsf4);
   compm4.Add(paramsf4);
   npm4.Add(paramsf4);
   fact = Factory(paramsf4,0.2);
   ecosysteme.getMilieu().listeFactories.push_back(fact);

   ecosysteme.run();


   return 0;

}
