#ifndef _CAMO_H_
#define _CAMO_H_

#include "UImg.h"
#include "DBestiole.h"
#include "Membre.h"
#include <iostream>
class Milieu;

using namespace std;

/**Paramètres pour construire des Camouflages*/
struct CamoParams:BParams
{
   double phi;
   /**Ajouter les paramètres au dictionnaire de paramètres*/
   virtual void Add(Param_Dict& pd) override;
   /**Copier ces paramètres*/
   virtual BParams* cppm() const override;
};
/**Camouflages*/
class Camouflages: public Membre
{
private:
   double phi;
public :     
   /**Constructeur*/                                   
   Camouflages(DBestiole* dbestiole,double phi); 
   /**Destructeur*/    
   virtual ~Camouflages();       
   /**Dessiner les camouflages*/                       
   virtual void draw( UImg & support ) override;
   /**Obtenir la visibilité avec les camouflages*/
   virtual double getVisibilite() const override;
   /**copier les camouflages*/
   virtual DBestiole* copy() override;
};

#endif
