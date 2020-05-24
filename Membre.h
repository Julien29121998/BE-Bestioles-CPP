#ifndef _MEMBRE_H_
#define _MEMBRE_H_

#include "UImg.h"
#include "DBestiole.h"
#include <iostream>
class Milieu;

using namespace std;

/**Un membre de Bestiole: Application de Décorateur*/
class Membre: public DBestiole
{
private :
   DBestiole*        mybestiole;//Bestiole décorée par le décorateur membre

public :
   /**Constructeur de Membre*/                                        
   Membre(DBestiole* dbestiole);  
   /**Destructeur de Membre*/   
   virtual ~Membre(); 
   /**Agir*/                             
   virtual void action( Milieu & monMilieu) override;
   /**Dessiner la bestiole*/
   virtual void draw( UImg & support ) override;
   /**Bouger la bestiole*/
   virtual void bouge( Milieu& monMilieu, double coef, paire_t objectif) override;
   /**Détecter une autre bestiole*/
   virtual bool jeTeVois( const DBestiole* b ) const override;
   /**Initialiser les coordonnées de la bestiole*/
   virtual void initCoords( int xLim, int yLim ) override;
   /**Renvoyer la visibilité de la bestiole*/
   virtual double getVisibilite() const override;
   /**Obtenir la resitance de la bestiole*/
   virtual double getResist() const override;
   /**Essayer de cloner la bestiole*/
   virtual DBestiole* randomCloning() const override;
   /**Faire vieillir la bestiole*/
   virtual bool vieillir() override;
   /**Copier la bestiole*/
   virtual DBestiole* copy() override;
   /**Définir la couche externe de décorateur de la bestiole*/
   virtual void setExterne(DBestiole* p) override;
   /**Récupérer les coordonnées de la bestiole*/
   virtual paire_t getCoords() const override;
   /**Tuer la bestiole*/
   virtual void killMe() override;
   /**Redéfinir les coordonnées de la bestiole*/
   virtual void setCoords(paire_t coords) override;
   /**Obtenir le type de la bestiole*/
   virtual string getType() const override;
   /**Définir le type de la bestiole*/
   virtual void setType(string type) override;
};

#endif
