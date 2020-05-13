#include "Nageoire.h"

#include <cstdlib>
#include <cmath>
#include "Milieu.h"

Nageoire::Nageoire(DBestiole* dbestiole,double nu):Membre(dbestiole),nu(((nu>MAX_NU)?MAX_NU:((nu<1)?1:nu)))
{
   cout<<"const Nageoire"<<endl;
}     
Nageoire::~Nageoire()
{
   cout<<"dest Nageoire"<<endl;

}                              
void Nageoire::draw( UImg & support )
{
   Membre::draw(support);
   paire_t coords = Membre::getCoords();
   T* grey = new T[ 3 ];
   grey[0]=92+38*(1-nu/MAX_NU);
   grey[1]=92+38*(1-nu/MAX_NU);
   grey[2]=92+38*(1-nu/MAX_NU);
   double xq = coords.x - cos( coords.ori)*AFF_SIZE/1.1;
   double yq = coords.y + sin( coords.ori)*AFF_SIZE/1.1;
   double xm = xq - cos( coords.ori)*AFF_SIZE/2.1;
   double ym = yq + sin( coords.ori)*AFF_SIZE/2.1;
   double xt = sin(coords.ori)*AFF_SIZE/3.4;
   double yt = cos(coords.ori)*AFF_SIZE/3.4;
   support.draw_triangle(xq,yq,xm+xt,ym+yt,xm-xt,ym-yt,grey);

}
void Nageoire::bouge(int xLim,int yLim,double coef){
   Membre::bouge(xLim,yLim, nu * coef);
}

DBestiole* Nageoire::copy()
{
   return new Nageoire(Membre::copy(),nu);
}