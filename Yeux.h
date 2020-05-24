#ifndef _YEUX_H_
#define _YEUX_H_

#include "UImg.h"
#include "DBestiole.h"
#include "Capteur.h"
#include <iostream>
class Milieu;

using namespace std;
/**Paramètres contenant les informations nécessaires pour construire des yeux*/
struct YeuxParams:BParams
{
   double delta;
   double gamma;
   double alpha;
   /**Ajouter ces paramètres dans un dictionnaire de paramètre*/
   virtual void Add(Param_Dict& pd) override;
   /**Copier ces paramètres*/
   virtual BParams* cppm() const override;
};
/**Yeux*/
class Yeux: public Capteur
{
private :
   double alpha;
   /**Vérifier que la bestiole observée est dans l'angle de vision*/
   bool dansAngle(const DBestiole* b) const;
public :                 
   /**Constructeur*/                       
   Yeux(DBestiole* dbestiole,double deltay, double gammay, double alpha);  
   /**Destructeur*/   
   virtual ~Yeux();  
   /**Est-ce que la bestiole peut voir la bestiole cible*/                            
   virtual bool jeTeVois(const DBestiole* b)const override;
   /**Afficher les yeux sur la bestiole*/
   virtual void draw( UImg & support ) override;
   /**Copier les yeux*/
   virtual DBestiole* copy() override;
};

#endif
