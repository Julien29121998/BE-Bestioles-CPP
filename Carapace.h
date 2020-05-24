#ifndef _CARA_H_
#define _CARA_H_

#include "UImg.h"
#include "DBestiole.h"
#include "Membre.h"
#include <iostream>
class Milieu;

using namespace std;
/**Paramètres de construction de carapace*/
struct CaraParams:BParams
{
   double omega;
   double eta;
   /**ajouter les paramètres à un dictionnaire de paramètres*/
   virtual void Add(Param_Dict& pd) override;
   /*Copier les paramètres*/
   virtual BParams* cppm() const override;
};
/**Carapace*/
class Carapace: public Membre
{
private:
   double omega;
   double eta;
public : 
   /**Constructeur*/                                       
   Carapace(DBestiole* dbestiole,double omega,double eta);
   /**Destructeur*/     
   virtual ~Carapace();        
   /**Dessiner une Carapace*/                      
   virtual void draw( UImg & support ) override;
   /**Resistance aux chocs avec une carapace*/
   virtual double getResist()const override;
   /**Se déplacer avec une carapace*/
   virtual void bouge(Milieu& monMilieu,double coef, paire_t objectif) override;
   /**Copier une carapace*/
   virtual DBestiole* copy() override;
};

#endif
