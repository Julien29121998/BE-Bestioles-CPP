#ifndef _CAMO_H_
#define _CAMO_H_

#include "UImg.h"
#include "DBestiole.h"
#include "Membre.h"
#include <iostream>
class Milieu;

using namespace std;

class Camouflages: public Membre
{
private:
   int phi;
public :                                        
   Camouflages(DBestiole* dbestiole);     
   virtual ~Camouflages();                              
   virtual void draw( UImg & support ) override;
   virtual double getVisibilite() const override;
   virtual DBestiole* copy() override;
};

#endif
