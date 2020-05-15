#include "Camouflages.h"

#include <cstdlib>
#include <cmath>
#include "Milieu.h"

void CamoParams::Add(Param_Dict& pd)
{
    PushWith(string("Camouflages"),pd);
}

Camouflages::Camouflages(DBestiole* dbestiole,double phi):Membre(dbestiole),phi(((phi>MAX_PHI)?MAX_PHI:((phi<MIN_PHI)?MIN_PHI:phi)))
{
   cout<<"const Camouflages"<<endl;
}     
Camouflages::~Camouflages()
{
   cout<<"dest Camouflages et ";

}                              
void Camouflages::draw( UImg & support )
{
   Membre::draw(support);
   paire_t coords = getCoords();
   T* green = new T[ 3 ];
   green[0]=static_cast<int>(68*(1-phi/2));
   green[1]=static_cast<int>(218*(1-phi/2));
   green[2]=static_cast<int>(66*(1-phi/2));
   double xc = coords.x - cos( coords.ori )*AFF_SIZE/1.6;
   double yc = coords.y - sin( coords.ori )*AFF_SIZE/1.6;
   support.draw_ellipse( xc, yc, AFF_SIZE/3.1, AFF_SIZE/3.7, coords.ori/M_PI*180.,green);
}
double Camouflages::getVisibilite() const
{
   return phi+Membre::getVisibilite();
}
DBestiole* Camouflages::copy()
{
   return new Camouflages(Membre::copy(),phi);
}