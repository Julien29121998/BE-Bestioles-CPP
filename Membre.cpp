#include "Membre.h"

#include <cstdlib>
#include <cmath>
#include "Milieu.h"

Membre::Membre(DBestiole* dbestiole){//Constructeur de Membre, défini en tant que décorateur d'une bestiole
    mybestiole=dbestiole;
    //cout<<"const membre : ";
}     
Membre::~Membre(){//Destructeur récursif de Membre/Bestiole
    delete mybestiole;
    //cout<<"dest membre : ";
}                              
void Membre::action( Milieu & monMilieu){//Agir: on fait agir la bestiole décorée
    mybestiole->action(monMilieu);
}
void Membre::draw( UImg & support ){//Dessiner: on dessine la bestiole décorée
    mybestiole->draw(support);
}
void Membre::bouge(Milieu& monMilieu, double coef, paire_t objectif){//Bouger: on fait bouger la bestiole décorée
    mybestiole->bouge(monMilieu,coef,objectif);
}
bool Membre::jeTeVois( const DBestiole* b ) const{//Percevoir: on utilise la perception des niveaux inférieurs
    return(mybestiole->jeTeVois(b));
}
void Membre::initCoords( int xLim, int yLim ){//Initialiser les coordonnées: récursivement
    mybestiole->initCoords(xLim,yLim);
}
double Membre::getVisibilite() const{//Récupérer la visibilité: visibilité de la bestiole décorée
    return(mybestiole->getVisibilite());
}
double Membre::getResist() const{//Récupérer la resistance: resistance de la bestiole décorée
    return(mybestiole->getResist());
}
DBestiole* Membre::randomCloning() const{//Clonage: on remonte jusqu'à la couche interne
    return(mybestiole->randomCloning());
}
bool Membre::vieillir(){//Vieillir: on fait vieillir la couche intérieure
    return(mybestiole->vieillir());
}
void Membre::setExterne(DBestiole* p){//Définir la couche externe: définir la couche externe de la bestiole décorée
    mybestiole->setExterne(p);
}
paire_t Membre::getCoords() const{//récupérer les coordonnées: récupérer les coordonnées de la bestiole décorée
    return mybestiole->getCoords();
}
DBestiole* Membre::copy()//Copier: copier la bestiole décorée
{
   return mybestiole->copy();
}
void Membre::killMe(){//Tuer la bestiole: remonter jusqu'à la bestiole interne
    mybestiole->killMe();
}
void Membre::setCoords(paire_t coords){//Définir les coordonnées: définir les coordonnées de la bestiole décorée
    return mybestiole->setCoords(coords);
}
string Membre::getType() const{//Récupérer le type: type de la bestiole décorée
    return mybestiole->getType();
}
void Membre::setType(string type){//définir le type: type de la bestiole décorée
    mybestiole->setType(type);
}