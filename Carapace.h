#ifndef _CARA_H_
#define _CARA_H_

#include "UImg.h"
#include "DBestiole.h"
#include "Membre.h"
#include <iostream>
class Milieu;

using namespace std;

struct CaraParams:BParams
{
   double omega;
   double eta;
   virtual void Add(Param_Dict& pd) override;
   virtual BParams* cppm() const override;
};

class Carapace: public Membre
{
private:
   double omega;
   double eta;
public :                                        
   Carapace(DBestiole* dbestiole,double omega,double eta);     
   virtual ~Carapace();                              
   virtual void draw( UImg & support ) override;
   virtual double getResist()const override;
   virtual void bouge(Milieu& monMilieu,double coef, paire_t objectif) override;
   virtual DBestiole* copy() override;
};

#endif
