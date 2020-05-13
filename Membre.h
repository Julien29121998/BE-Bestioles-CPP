#ifndef _MEMBRE_H_
#define _MEMBRE_H_

#include "UImg.h"
#include "DBestiole.h"
#include <iostream>
class Milieu;

using namespace std;

class Membre: public DBestiole
{
private :
   DBestiole*        mybestiole;

public :                                        
   Membre(DBestiole* dbestiole);     
   virtual ~Membre();                              
   virtual void action( Milieu & monMilieu) override;
   virtual void draw( UImg & support ) override;
   virtual void bouge( int xLim, int yLim, double coef ) override;
   virtual bool jeTeVois( const DBestiole* b ) const override;
   virtual void initCoords( int xLim, int yLim ) override;
   virtual double getVisibilite() const override;
   virtual double getResist() const override;
   virtual DBestiole* randomCloning() const override;
   virtual bool vieillir() override;
   virtual DBestiole* copy() override;
   virtual void setExterne(DBestiole* p) override;
   virtual paire_t getCoords() const override;
};

#endif
