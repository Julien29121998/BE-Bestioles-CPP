#include "Nageoire.h"

#include <cstdlib>
#include <cmath>
#include "Milieu.h"

void NageoParams::Add(Param_Dict& pd)
{
    PushWith(string("Nageoire"),pd);
}

Nageoire::Nageoire(DBestiole* dbestiole,double nu):Membre(dbestiole),nu(((nu>MAX_NU)?MAX_NU:((nu<1)?1:nu)))
{
   cout<<"const Nageoire"<<endl;
}     
Nageoire::~Nageoire()
{
   cout<<"dest Nageoire et ";

}                              
void Nageoire::draw( UImg & support )
{
   Membre::draw(support);
   paire_t coords = getCoords();
   T* grey = new T[ 3 ];
   grey[0]=92+38*(1-nu/MAX_NU);
   grey[1]=92+38*(1-nu/MAX_NU);
   grey[2]=92+38*(1-nu/MAX_NU);
   double xq = coords.x - cos( coords.ori)*AFF_SIZE/1.1;
   double yq = coords.y - sin( coords.ori)*AFF_SIZE/1.1;
   double xm = xq - cos( coords.ori)*AFF_SIZE/1.8;
   double ym = yq - sin( coords.ori)*AFF_SIZE/1.8;
   double xd = -sin(coords.ori)*AFF_SIZE/3.1;
   double yd = cos(coords.ori)*AFF_SIZE/3.1;
   support.draw_triangle(xq,yq,xm+xd,ym+yd,xm-xd,ym-yd,grey);

}
void Nageoire::bouge(Milieu& monMilieu,double coef, paire_t objectif){
   Membre::bouge(monMilieu, nu * coef, objectif);
}

DBestiole* Nageoire::copy()
{
   return new Nageoire(Membre::copy(),nu);
}