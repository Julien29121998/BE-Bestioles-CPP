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
   CamoParams cpm;
   CaraParams kpm;
   NageoParams npm;
   OreParams opm;
   YeuxParams ypm;
   Param_Dict     params;
   Aquarium       ecosysteme( 28, 800, 600, 30 );

   params.erase(params.begin(),params.end());
   kpm.eta = 2.;
   kpm.omega = 2.8;
   cpm.phi=0.8;
   kpm.Add(params);
   cpm.Add(params);
   cout<<params.size()<<endl;
   Factory fact = Factory(params,0.25);
   ecosysteme.getMilieu().listeFactories.push_back(fact);

   params.erase(params.begin(),params.end());
   opm.delta=18.5;
   opm.gamma=0.9;
   npm.nu = 3.1;
   cpm.phi=0.2;
   opm.Add(params);
   npm.Add(params);
   cpm.Add(params);
   cout<<params.size()<<endl;
   fact = Factory(params,0.25);
   ecosysteme.getMilieu().listeFactories.push_back(fact);

   params.erase(params.begin(),params.end());
   ypm.delta=48.6;
   ypm.gamma=0.4;
   ypm.alpha=0.78;
   ypm.Add(params);
   cout<<params.size()<<endl;
   fact = Factory(params,0.25);
   ecosysteme.getMilieu().listeFactories.push_back(fact);

   params.erase(params.begin(),params.end());
   ypm.delta=31.;
   ypm.gamma=0.4;
   ypm.alpha=0.66;
   opm.delta=16.9;
   opm.gamma=0.88;
   ypm.Add(params);
   opm.Add(params);
   cout<<params.size()<<endl;
   fact = Factory(params,0.25);
   ecosysteme.getMilieu().listeFactories.push_back(fact);

   ecosysteme.run();


   return 0;

}
