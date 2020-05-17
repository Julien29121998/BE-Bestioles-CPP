#include "Carapace.h"

#include <cstdlib>
#include <cmath>
#include "Milieu.h"

void CaraParams::Add(Param_Dict& pd)
{
    PushWith(string("Carapace"),pd);
}

Carapace::Carapace(DBestiole* dbestiole,double omega, double eta):Membre(dbestiole),
omega(((omega>MAX_OMEGA)?MAX_OMEGA:((omega<1)?1:omega))),
eta(((eta>MAX_ETA)?MAX_ETA:((eta<1)?1:eta)))
{
   cout<<"const Carapace"<<endl;
}     
Carapace::~Carapace()
{
   cout<<"dest Carapace et ";

}                              
void Carapace::draw( UImg & support )
{
   Membre::draw(support);
   paire_t coords = getCoords();
   T* lightbrown = new T[ 3 ];
   lightbrown[0]=150-38*(omega/MAX_OMEGA);
   lightbrown[1]=112;
   lightbrown[2]=22+60*(1-(eta/MAX_ETA));
   support.draw_circle(coords.x,coords.y,AFF_SIZE/2.3,lightbrown);

}
double Carapace::getResist()const{
   return omega*Membre::getResist();
}
void Carapace::bouge(Milieu& monMilieu,double coef){
   Membre::bouge(monMilieu, coef/eta);
}

DBestiole* Carapace::copy()
{
   return new Carapace(Membre::copy(),omega, eta);
}