#ifndef _CAPTEUR_H_
#define _CAPTEUR_H_

#include "UImg.h"
#include "DBestiole.h"
#include "Membre.h"
#include <iostream>
class Milieu;

using namespace std;

/**Capteurs: Yeux ou Oreilles*/
class Capteur: public Membre
{
protected:
   double delta;
   double gamma;
   /**Evaluer si la bestiole cible est assez proche pour ces capteurs*/
   bool assezProche(const DBestiole* b) const;
   /**Evaluer si les capteurs sont assez efficaces pour les camouflages cibles*/
   bool assezEfficace(const DBestiole* b) const;
public :
   /**Constructeur*/                                        
   Capteur(DBestiole* dbestiole,double delta, double gamma);   
   /**Destructeur*/
   virtual ~Capteur();                              
};

#endif
