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
}
double Camouflages::getVisibilite() const
{
   return phi+Membre::getVisibilite();
}
DBestiole* Camouflages::copy()
{
   return new Camouflages(Membre::copy(),phi);
}