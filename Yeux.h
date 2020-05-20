#ifndef _YEUX_H_
#define _YEUX_H_

#include "UImg.h"
#include "DBestiole.h"
#include "Capteur.h"
#include <iostream>
class Milieu;

using namespace std;

struct YeuxParams:BParams
{
   double delta;
   double gamma;
   double alpha;
   virtual void Add(Param_Dict& pd) override;
   virtual BParams* cppm() const override;
};

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
