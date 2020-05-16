#ifndef _DBESTIOLE_H_
#define _DBESTIOLE_H_


#include "UImg.h"

#include <iostream>
#include <map>

class Milieu;
struct BParams;

using namespace std;
using Param_Dict = std::map<std::string,BParams*>;


typedef struct paire {
   int x;
   int y;
   double ori;
   double vite;

} paire_t;

struct BParams
{
virtual ~BParams();
void PushWith(string key,Param_Dict& pd);
virtual void Add(Param_Dict& pd)=0;
};

class DBestiole{
friend class Milieu;
protected :
   static const double     AFF_SIZE;
   static const double     MAX_VITESSE;
   static const double     MAX_PHI;
   static const double     MIN_PHI;
   static const double     MAX_DELTA_O;
   static const double     MIN_DELTA_O;
   static const double     MAX_GAMMA_O;
   static const double     MIN_GAMMA_O;
   static const double     MAX_DELTA_Y;
   static const double     MIN_DELTA_Y;
   static const double     MAX_GAMMA_Y;
   static const double     MIN_GAMMA_Y;
   static const double     MAX_ALPHA;
   static const double     MIN_ALPHA;  
   static const double     MAX_NU;
   static const double     MAX_OMEGA;
   static const double     MAX_ETA;
   static const double     GENERATION_RATE;
   static const double     CLONE_RATE;
   static const int        LIFE;

private :
   static long int              next;
   long int                     identite;
 
public :                                      
   DBestiole();                               
   virtual ~DBestiole();                     
   char* showID() const;
   virtual void action( Milieu & monMilieu)=0;
   virtual void draw( UImg & support )=0;
   virtual void bouge(Milieu& monMilieu, double coef )=0;
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
   virtual void setCoords(paire_t coords)=0;

};


#endif
