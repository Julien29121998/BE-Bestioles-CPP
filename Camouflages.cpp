#include "Camouflages.h"

#include <cstdlib>
#include <cmath>
#include "Milieu.h"

void CamoParams::Add(Param_Dict& pd)//ajouter les paramètres de camouflages à un dictionnaire de paramètres
{
    PushWith(string("Camouflages"),pd);//ils sont ajoutés en tant que paramètres
}

BParams* CamoParams::cppm() const{//copier les paramètres de Camouflages
   CamoParams* p = new CamoParams();
   p->phi=this->phi;
   return p;//retour de la copie
}

Camouflages::Camouflages(DBestiole* dbestiole,double phi):Membre(dbestiole),phi(((phi>MAX_PHI)?MAX_PHI:((phi<MIN_PHI)?MIN_PHI:phi)))//Constructeur: on place la valeur dans l'intervalle
{
   //cout<<"const Camouflages"<<endl;
}     
Camouflages::~Camouflages()//Destructeur
{
   //cout<<"dest Camouflages et ";

}                              
void Camouflages::draw( UImg & support )//Dessiner des camouflages
{
   Membre::draw(support);//On dessine le reste
   paire_t coords = getCoords();//mes coordonnées
   T green[3];//Vert
   green[0]=static_cast<int>(68*(1-phi/2));//vert d'intensité dépendant de l'efficacité
   green[1]=static_cast<int>(218*(1-phi/2));//vert d'intensité dépendant de l'efficacité
   green[2]=static_cast<int>(66*(1-phi/2));//vert d'intensité dépendant de l'efficacité
   double xc = coords.x - cos( coords.ori )*AFF_SIZE/1.6;//milieu du corps
   double yc = coords.y - sin( coords.ori )*AFF_SIZE/1.6;//milieu du corps
   support.draw_ellipse( xc, yc, AFF_SIZE/3.1, AFF_SIZE/3.7, coords.ori/M_PI*180.,green);//ellipse
}
double Camouflages::getVisibilite() const //visibilité avec les camouflages
{
   return phi+Membre::getVisibilite();//visibilité de base + visibilité avec les camouflages
}
DBestiole* Camouflages::copy()//copie des camouflages
{
   return new Camouflages(Membre::copy(),phi);
}