#ifndef _NAG_H_
#define _NAG_H_

#include "UImg.h"
#include "DBestiole.h"
#include "Membre.h"
#include <iostream>
class Milieu;

using namespace std;

struct NageoParams:BParams
{
   double nu;
   virtual void Add(Param_Dict& pd) override;
   virtual BParams* cppm() const override;

};

class Nageoire: public Membre
{
private:
   double nu;
public :                                        
   Nageoire(DBestiole* dbestiole,double nu);     
   virtual ~Nageoire();                              
   virtual void draw( UImg & support ) override;
   virtual void bouge(Milieu& monMilieu,double coef, paire_t objectif) override;
   virtual DBestiole* copy() override;
};

#endif
