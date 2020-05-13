#include "Camouflages.h"

#include <cstdlib>
#include <cmath>
#include "Milieu.h"

Camouflages::Camouflages(DBestiole* dbestiole,int phi):Membre(dbestiole),phi(phi)
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
   green[0]=58;
   green[1]=192;
   green[2]=57;
   double         xc = coords.x - cos( coords.ori )*AFF_SIZE/1.7;
   double         yc = coords.y + sin( coords.ori )*AFF_SIZE/1.7;
   support.draw_ellipse( xc, yc, AFF_SIZE/1.9, AFF_SIZE/4.4, -coords.ori/M_PI*180.,green);
}
double Camouflages::getVisibilite() const
{
   return phi+Membre::getVisibilite();
}
DBestiole* Camouflages::copy()
{
   return new Camouflages(Membre::copy(),phi);
}