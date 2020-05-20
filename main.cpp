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
#include "Interpreter.h"

#include <iostream>

using namespace std;


int main()
{

   Aquarium       ecosysteme( 60, 800, 600, 30 );
   Interpreter i;

   Param_Dict paramsf;
   CamoParams* cpm = new CamoParams;
   CaraParams* kpm = new CaraParams;
   NageoParams* npm = new NageoParams;
   OreParams* opm = new OreParams;
   YeuxParams* ypm = new YeuxParams;
   ComportParams* compm = new ComportParams;
   
   paramsf.erase(paramsf.begin(),paramsf.end());
   kpm->eta = 2.6;
   kpm->omega = 3.8;
   kpm->Add(paramsf);
   cpm->phi=0.1;
   cpm->Add(paramsf);
   opm->delta=26.5;
   opm->gamma=0.3;
   opm->Add(paramsf);
   compm->Comportement=COMP_GREGAIRE;
   compm->Add(paramsf);
   Factory fact = Factory(paramsf,0.25);
   ecosysteme.getMilieu().listeFactories.push_back(fact);

   paramsf.erase(paramsf.begin(),paramsf.end());
   opm->delta=18.5;
   opm->gamma=0.9;
   opm->Add(paramsf);
   npm->nu = 2.6;
   npm->Add(paramsf);
   cpm->phi=0.2;
   cpm->Add(paramsf);
   compm->Comportement=COMP_PREVOYANTE;
   compm->Add(paramsf);
   fact = Factory(paramsf,0.25);
   ecosysteme.getMilieu().listeFactories.push_back(fact);

   paramsf.erase(paramsf.begin(),paramsf.end());
   ypm->delta=48.6;
   ypm->gamma=0.4;
   ypm->alpha=0.78;
   compm->Comportement=COMP_MULTIPLE;
   ypm->Add(paramsf);
   compm->Add(paramsf);
   fact = Factory(paramsf,0.25);
   ecosysteme.getMilieu().listeFactories.push_back(fact);

   paramsf.erase(paramsf.begin(),paramsf.end());
   ypm->delta=31.;
   ypm->gamma=0.4;
   ypm->alpha=0.66;
   opm->delta=16.9;
   opm->gamma=0.88;
   npm->nu=1.8;
   compm->Comportement=COMP_KAMIKAZE;
   ypm->Add(paramsf);
   opm->Add(paramsf);
   compm->Add(paramsf);
   npm->Add(paramsf);
   fact = Factory(paramsf,0.25);
   ecosysteme.getMilieu().listeFactories.push_back(fact);


   delete cpm;
   delete kpm;
   delete npm;
   delete opm;
   delete ypm;
   delete compm;


   ecosysteme.run();


   return 0;

}
