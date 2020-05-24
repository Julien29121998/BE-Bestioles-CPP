#ifndef _BESTIOLES_H_
#define _BESTIOLES_H_


#include "UImg.h"
#include "DBestiole.h"
#include "Comportement.h"
#include <iostream>
class Milieu;

using namespace std;

class Bestiole: public DBestiole
{
private :
   unsigned int               age;
   unsigned int         esperance;
   int               x, y;
   double            cumulX, cumulY;
   double            orientation;
   double            vitesse;
   DBestiole*        coucheExterne;
   IComportement*    comportement;
   T*                couleur;
   string            type;

public :           
   /**Constructeur*/                             
   Bestiole(IComportement* comp); 
   /**Constructeur paramétré pour clonage*/    
   Bestiole(int _x, int _y,double _v, double _o, T* _couleur, IComportement* comp);    
   /**Destructeur*/                    
   virtual ~Bestiole();              
   /**Agir selon un comportement*/                
   virtual void action( Milieu & monMilieu) override;
   /**Dessiner la Bestiole*/
   virtual void draw( UImg & support ) override;
   /**se déplacer dans le milieu*/
   virtual void bouge(Milieu& monMilieu, double coef, paire_t objectif ) override;
   /**tester la perception d'une autre bestiole*/
   virtual bool jeTeVois( const DBestiole* b ) const override;
   /**Initialiser aléatoirement les coordonnées*/
   virtual void initCoords( int xLim, int yLim ) override;
   /**Obtenir la visibilité de la bestiole*/
   virtual double getVisibilite() const override;
   /**Obtenir la résistance de la bestiole*/
   virtual double getResist() const override;
   /*Essayer de cloner la bestiole*/
   virtual DBestiole* randomCloning() const override;
   /*faire vieillir la bestiole*/
   virtual bool vieillir() override;
   /*Produire une copie de la bestiole*/
   virtual DBestiole* copy() override;
   /*Enseigner à la bestiole son décorateur le plus externe*/
   virtual void setExterne(DBestiole* p) override;
   /*connaitre les coordonnées de la bestiole*/
   virtual paire_t getCoords() const override;
   /*tuer la bestiole*/
   virtual void killMe() override;
   /*définir les coordonnées de la bestiole*/
   virtual void setCoords(paire_t coords) override;
   /*Obtenir le type de la bestiole*/
   virtual string getType() const override;
   /*Définir le type de la bestiole*/
   virtual void setType(string ntype) override;

};


#endif
