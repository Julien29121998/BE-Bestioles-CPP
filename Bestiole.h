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
   Bestiole(IComportement* comp);     
   Bestiole(int _x, int _y,double _v, double _o, T* _couleur, IComportement* comp);                        
   virtual ~Bestiole();                              
   virtual void action( Milieu & monMilieu) override;
   virtual void draw( UImg & support ) override;
   virtual void bouge(Milieu& monMilieu, double coef, paire_t objectif ) override;
   virtual bool jeTeVois( const DBestiole* b ) const override;
   virtual void initCoords( int xLim, int yLim ) override;
   virtual double getVisibilite() const override;
   virtual double getResist() const override;
   virtual DBestiole* randomCloning() const override;
   virtual bool vieillir() override;
   virtual DBestiole* copy() override;
   virtual void setExterne(DBestiole* p) override;
   virtual paire_t getCoords() const override;
   virtual void killMe() override;
   virtual void setCoords(paire_t coords) override;
   virtual string getType() const override;
   virtual void setType(string ntype) override;

};


#endif
