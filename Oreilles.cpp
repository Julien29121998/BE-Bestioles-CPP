#include "Oreilles.h"

#include <cstdlib>
#include <cmath>
#include "Milieu.h"

void OreParams::Add(Param_Dict& pd)
{
    PushWith(string("Oreilles"),pd);
}

BParams* OreParams::cppm() const{
   OreParams* p = new OreParams();
   p->delta=this->delta;
   p->gamma=this->gamma;
   return p;
}

Oreilles::Oreilles(DBestiole* dbestiole,double deltao, double gammao):
Capteur(dbestiole,
((deltao>MAX_DELTA_O)?MAX_DELTA_O:((deltao<MIN_DELTA_O)?MIN_DELTA_O:deltao)),
((gammao>MAX_GAMMA_O)?MAX_GAMMA_O:((gammao<MIN_GAMMA_O)?MIN_GAMMA_O:gammao)))
{
   cout<<"const Oreilles"<<endl;
}     
Oreilles::~Oreilles()
{
   cout<<"dest Oreilles et ";

}                              
bool Oreilles::jeTeVois(const DBestiole* b) const{
   return((this->assezProche(b)&&this->assezEfficace(b))||Capteur::jeTeVois(b));
}
DBestiole* Oreilles::copy()
{
   return new Oreilles(Capteur::copy(),delta, gamma);
}
void Oreilles::draw( UImg & support )
{
   Capteur::draw(support);
   paire_t coords = getCoords();
   double xt = coords.x + cos(coords.ori)*AFF_SIZE/2.1;
   double yt = coords.y + sin(coords.ori)*AFF_SIZE/2.1;
   double xd = -sin(coords.ori)*AFF_SIZE/1.8;
   double yd = cos(coords.ori)*AFF_SIZE/1.8;
   T* red = new T[ 3 ];
   red[0]=182;
   red[1]=10;
   red[2]=10;
   support.draw_circle(xt+xd,yt+yd,AFF_SIZE/3.7,red);
   support.draw_circle(xt-xd,yt-yd,AFF_SIZE/3.7,red);
}