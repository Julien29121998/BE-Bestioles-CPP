#ifndef _NAG_H_
#define _NAG_H_

#include "UImg.h"
#include "DBestiole.h"
#include "Membre.h"
#include <iostream>
class Milieu;

using namespace std;
/**Paramètres pour construire des nageoires*/
struct NageoParams:BParams
{
   double nu;
   /**Ajouter les paramètres de nageoires à un dictionnaire de paramètres*/
   virtual void Add(Param_Dict& pd) override;
   /**Copie des paramètres de nageoires*/
   virtual BParams* cppm() const override;

};
/**Nagoire*/
class Nageoire: public Membre
{
private:
   double nu;
public : 
   /**Constructeur de Nageoire*/                                       
   Nageoire(DBestiole* dbestiole,double nu); 
   /**Destructeur de Nageoire*/    
   virtual ~Nageoire();        
   /**Dessiner la nageoire*/                      
   virtual void draw( UImg & support ) override;
   /**Déplacer la bestiole avec la nageoire*/
   virtual void bouge(Milieu& monMilieu,double coef, paire_t objectif) override;
   /**Copier la nageoire*/
   virtual DBestiole* copy() override;
};

#endif
