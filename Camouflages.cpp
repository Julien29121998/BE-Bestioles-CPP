#include "Camouflages.h"

#include <cstdlib>
#include <cmath>
#include "Milieu.h"

Camouflages::Camouflages(DBestiole* dbestiole,double phi):Membre(dbestiole),phi(((phi>LIMITE_PHI)?LIMITE_PHI:((phi<0)?0:phi)))
{
   cout<<"const Camouflages"<<endl;
}     
Camouflages::~Camouflages()
{
   cout<<"dest Camouflages"<<endl;

}                              
void Camouflages::draw( UImg & support )
{
   Membre::draw(support);
   paire_t coords = Membre::getCoords();
   T* green = new T[ 3 ];
   green[0]=static_cast<int>(68*(1-phi));
   green[1]=static_cast<int>(218*(1-phi));
   green[2]=static_cast<int>(66*(1-phi));
   double xc = coords.x - cos( coords.ori )*AFF_SIZE/1.7;
   double yc = coords.y + sin( coords.ori )*AFF_SIZE/1.7;
   support.draw_ellipse( xc, yc, AFF_SIZE/3.1, AFF_SIZE/3.6, -coords.ori/M_PI*180.,green);
}
double Camouflages::getVisibilite() const
{
   return phi+Membre::getVisibilite();
}
DBestiole* Camouflages::copy()
{
   return new Camouflages(Membre::copy(),phi);
}