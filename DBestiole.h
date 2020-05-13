#ifndef _DBESTIOLE_H_
#define _DBESTIOLE_H_


#include "UImg.h"

#include <iostream>
using namespace std;
class Milieu;
typedef struct paire {
   int x;
   int y;
   double ori;

} paire_t;

class DBestiole{
friend class Milieu;
protected :
   static const double     AFF_SIZE;
   static const double     MAX_VITESSE;
   static const double     MAX_PHI;
   static const double     MIN_PHI;
   static const double     MAX_NU;
   static const double     MAX_OMEGA;
   static const double     MAX_ETA;
   static const double     LIMITE_VUE;
   static const int        LIFE;
   static const int        CLONE_RATE;

private :
   static int              next;
   int                     identite;
 
public :                                      
   DBestiole();                               
   virtual ~DBestiole();                     
   char* showID() const;
   virtual void action( Milieu & monMilieu)=0;
   virtual void draw( UImg & support )=0;
   virtual void bouge( int xLim, int yLim, double coef )=0;
   virtual bool jeTeVois( const DBestiole* b ) const=0;
   virtual void initCoords( int xLim, int yLim )=0;
   virtual double getVisibilite() const=0;
   virtual double getResist() const=0;
   virtual DBestiole* randomCloning() const=0;
   virtual bool vieillir()=0;
   virtual void setExterne(DBestiole* p)=0;
   virtual DBestiole* copy()=0;
   virtual paire_t getCoords() const=0;
   virtual void killMe()=0;
};


#endif
