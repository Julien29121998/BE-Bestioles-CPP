#ifndef _NAG_H_
#define _NAG_H_

#include "UImg.h"
#include "DBestiole.h"
#include "Membre.h"
#include <iostream>
class Milieu;

using namespace std;

class Nageoire: public Membre
{
private:
   double nu;
public :                                        
   Nageoire(DBestiole* dbestiole,double nu);     
   virtual ~Nageoire();                              
   virtual void draw( UImg & support ) override;
   virtual void bouge(int xLim,int yLim,double coef) override;
   virtual DBestiole* copy() override;
};

#endif
