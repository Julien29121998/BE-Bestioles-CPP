#include "Capteur.h"

#include <cstdlib>
#include <cmath>
#include "Milieu.h"

Capteur::Capteur(DBestiole* dbestiole,double delta, double gamma):Membre(dbestiole),delta(delta),gamma(gamma)
{
   cout<<"const Capteur : ";
}     
Capteur::~Capteur()
{
   cout<<"dest Capteur et ";

}
bool Capteur::assezProche(const DBestiole* that)const{
   double dist;
   paire_t myCoords= this->getCoords();
   paire_t itsCoords= that->getCoords();
   dist = std::sqrt( (myCoords.x-itsCoords.x)*(myCoords.x-itsCoords.x) + (myCoords.y-itsCoords.y)*(myCoords.y-itsCoords.y) );
   return ( dist <= delta );
}
bool Capteur::assezEfficace(const DBestiole* that)const{
   return(that->getVisibilite()<this->gamma);
}