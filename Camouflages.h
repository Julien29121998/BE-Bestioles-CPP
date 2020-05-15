#ifndef _CAMO_H_
#define _CAMO_H_

#include "UImg.h"
#include "DBestiole.h"
#include "Membre.h"
#include <iostream>
class Milieu;

using namespace std;

struct CamoParams:BParams
{
   double phi;
   virtual void Add(Param_Dict& pd) override;
};

class Camouflages: public Membre
{
private:
   double phi;
public :                                        
   Camouflages(DBestiole* dbestiole,double phi);     
   virtual ~Camouflages();                              
   virtual void draw( UImg & support ) override;
   virtual double getVisibilite() const override;
   virtual DBestiole* copy() override;
};

#endif
