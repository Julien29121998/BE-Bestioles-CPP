#include "Capteur.h"

#include <cstdlib>
#include <cmath>
#include "Milieu.h"

Capteur::Capteur(DBestiole* dbestiole,double delta, double gamma):Membre(dbestiole),delta(delta),gamma(gamma)//constructeur de capteurs
{
   //cout<<"const Capteur : ";
}     
Capteur::~Capteur()//destructeur de capteurs
{
  //cout<<"dest Capteur et ";

}
bool Capteur::assezProche(const DBestiole* that)const{//la bestiole à percevoir est-elle assez proche ?
   double dist;
   paire_t myCoords= this->getCoords();//mes coordonnées
   paire_t itsCoords= that->getCoords();//ses coordonnées
   dist = std::sqrt( (myCoords.x-itsCoords.x)*(myCoords.x-itsCoords.x) + (myCoords.y-itsCoords.y)*(myCoords.y-itsCoords.y) );//norme de la distance
   return ( dist <= delta );//distance inférieure à mon delta
}
bool Capteur::assezEfficace(const DBestiole* that)const{//les capteurs sont ils assez efficaces pour ses camouflages ?
   return(that->getVisibilite()<this->gamma);//comparaison
}