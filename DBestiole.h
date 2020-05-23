#ifndef _DBESTIOLE_H_
#define _DBESTIOLE_H_


#include "UImg.h"

#include <iostream>
#include <map>

class Milieu;
class Interpreter;
struct BParams;

using namespace std;
using Param_Dict = std::map<std::string,BParams*>;


typedef struct paire {
   int x;
   int y;
   double ori;
   double vite;

} paire_t;
typedef struct exact_coords {
   double x;
   double y;
} xcoords_t;

struct BParams
{
BParams();
virtual ~BParams();
void PushWith(string key,Param_Dict& pd);
virtual void Add(Param_Dict& pd)=0;
virtual BParams* cppm() const=0;
};

class DBestiole{
friend class Milieu;
friend class Interpreter;
protected :
   static double     AFF_SIZE;
   static double     MAX_VITESSE;
   static double     MAX_PHI;
   static double     MIN_PHI;
   static double     MAX_DELTA_O;
   static double     MIN_DELTA_O;
   static double     MAX_GAMMA_O;
   static double     MIN_GAMMA_O;
   static double     MAX_DELTA_Y;
   static double     MIN_DELTA_Y;
   static double     MAX_GAMMA_Y;
   static double     MIN_GAMMA_Y;
   static double     MAX_ALPHA;
   static double     MIN_ALPHA;  
   static double     MAX_NU;
   static double     MAX_OMEGA;
   static double     MAX_ETA;
   static double     GENERATION_RATE;
   static double     CLONE_RATE;
   static double     SURVIVE_COLLISION;
   static double     PROPORTION_CHANGE;
   static int        LIFE;

private :
   static long int              next;
   long int                     identite;
 
public :                                      
   DBestiole();                               
   virtual ~DBestiole(); 
   static double getVmax(){return MAX_VITESSE;};                   
   char* showID() const;
   virtual void action( Milieu & monMilieu)=0;
   virtual void draw( UImg & support )=0;
   virtual void bouge(Milieu& monMilieu, double coef, paire_t objectif)=0;
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
   virtual string getType() const=0;
   virtual void setType(string type)=0;

};


#endif
