#ifndef _OREILLES_H_
#define _OREILLES_H_

#include "UImg.h"
#include "DBestiole.h"
#include "Capteur.h"
#include <iostream>
class Milieu;

using namespace std;

class Oreilles: public Capteur
{
public :                                        
   Oreilles(DBestiole* dbestiole,double deltao, double gammao);     
   virtual ~Oreilles();                              
   virtual bool jeTeVois(const DBestiole* b)const override;
   virtual void draw( UImg & support ) override;
   virtual DBestiole* copy() override;
};

#endif
