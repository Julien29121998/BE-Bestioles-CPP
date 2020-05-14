#ifndef _YEUX_H_
#define _YEUX_H_

#include "UImg.h"
#include "DBestiole.h"
#include "Capteur.h"
#include <iostream>
class Milieu;

using namespace std;

class Yeux: public Capteur
{
private :
   double alpha;
   bool dansAngle(const DBestiole* b) const;
public :                                        
   Yeux(DBestiole* dbestiole,double deltay, double gammay, double alpha);     
   virtual ~Yeux();                              
   virtual bool jeTeVois(const DBestiole* b)const override;
   virtual void draw( UImg & support ) override;
   virtual DBestiole* copy() override;
};

#endif
