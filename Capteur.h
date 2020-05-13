#ifndef _CAPTEUR_H_
#define _CAPTEUR_H_

#include "UImg.h"
#include "DBestiole.h"
#include "Membre.h"
#include <iostream>
class Milieu;

using namespace std;

class Capteur: public Membre
{
protected:
   double delta;
   double gamma;
   bool assezProche(const DBestiole* b) const;
   bool assezEfficace(const DBestiole* b) const;
public :                                        
   Capteur(DBestiole* dbestiole,double delta, double gamma);     
   virtual ~Capteur();                              
};

#endif
