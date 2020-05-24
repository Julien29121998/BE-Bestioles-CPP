#ifndef _OREILLES_H_
#define _OREILLES_H_

#include "UImg.h"
#include "DBestiole.h"
#include "Capteur.h"
#include <iostream>
class Milieu;

using namespace std;

/**Paramètres permettant de construire des oreilles*/
struct OreParams:BParams
{
   double delta;
   double gamma;
   /**Ajouter ces paramètres au dictionnaire des paramètres*/
   virtual void Add(Param_Dict& pd) override;
   /**Copier ces paramètres*/
   virtual BParams* cppm() const override;
};
/**Oreilles*/
class Oreilles: public Capteur
{
public :
   /**Constructeur*/                                        
   Oreilles(DBestiole* dbestiole,double deltao, double gammao);  
   /**Destructeur*/   
   virtual ~Oreilles();
   /**Est-ce que la bestiole peut voir la bestiole cible*/                            
   virtual bool jeTeVois(const DBestiole* b)const override;
   /**Dessine les Oreilles*/
   virtual void draw( UImg & support ) override;
   /**Copie les oreilles*/
   virtual DBestiole* copy() override;
};

#endif
