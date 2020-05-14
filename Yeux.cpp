#include "Yeux.h"

#include <cstdlib>
#include <cmath>
#include "Milieu.h"

Yeux::Yeux(DBestiole* dbestiole,double deltay, double gammay,double alpha):
Capteur(dbestiole,
((deltay>MAX_DELTA_Y)?MAX_DELTA_Y:((deltay<MIN_DELTA_Y)?MIN_DELTA_Y:deltay)),
((gammay>MAX_GAMMA_Y)?MAX_GAMMA_Y:((gammay<MIN_GAMMA_Y)?MIN_GAMMA_Y:gammay))),
alpha(((alpha>MAX_ALPHA)?MAX_ALPHA:((alpha<MIN_ALPHA)?MIN_ALPHA:alpha)))
{
   cout<<"const Yeux"<<endl;
}     
Yeux::~Yeux()
{
   cout<<"dest Yeux et ";

}
bool Yeux::dansAngle(const DBestiole* that) const{
   paire_t myCoords= this->getCoords();
   paire_t itsCoords= that->getCoords();
   double x_vect = itsCoords.x-myCoords.x;
   double y_vect = itsCoords.y-myCoords.y;
   double norm_vect = sqrt(x_vect*x_vect + y_vect*y_vect);
   double x_dir = cos(myCoords.ori);
   double y_dir = sin(myCoords.ori);
   double sc = (x_dir*x_vect+y_dir*y_vect)/norm_vect;
   double arc = acos(sc);
   return(sc>0&&abs(arc)<(alpha/2));
}
bool Yeux::jeTeVois(const DBestiole* b) const{
   return((this->assezProche(b)&&this->assezEfficace(b)&&this->dansAngle(b))||Capteur::jeTeVois(b));
}
DBestiole* Yeux::copy()
{
   return new Yeux(Capteur::copy(),delta, gamma,alpha);
}
void Yeux::draw( UImg & support )
{
   Capteur::draw(support);
   paire_t coords = getCoords();
   double xty = coords.x + cos(coords.ori)*AFF_SIZE;
   double yty = coords.y + sin(coords.ori)*AFF_SIZE;
   double xd = -sin(coords.ori)*AFF_SIZE/3.5;
   double yd = cos(coords.ori)*AFF_SIZE/3.5;
   T* blue = new T[ 3 ];
   blue[0]=4;
   blue[1]=38;
   blue[2]=129;
   support.draw_circle(xty+xd,yty+yd,AFF_SIZE/4.,blue);
   support.draw_circle(xty-xd,yty-yd,AFF_SIZE/4.,blue);
}