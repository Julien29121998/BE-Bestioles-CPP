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
}
double Camouflages::getVisibilite() const
{
   return phi;
}
DBestiole* Camouflages::copy()
{
   return new Camouflages(this->mybestiole->copy(),phi);
}