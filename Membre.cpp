#include "Membre.h"

#include <cstdlib>
#include <cmath>
#include "Milieu.h"

Membre::Membre(DBestiole* dbestiole){
    mybestiole=dbestiole;
    cout<<"const membre"<<endl;
}     
Membre::~Membre(){
    delete mybestiole;
    cout<<"dest membre"<<endl;
}                              
void Membre::action( Milieu & monMilieu){
    mybestiole->action(monMilieu);
}
void Membre::draw( UImg & support ){
    mybestiole->draw(support);
}
void Membre::bouge( int xLim, int yLim, double coef ){
    mybestiole->bouge(xLim,yLim,coef);
}
bool Membre::jeTeVois( const DBestiole* b ) const{
    return(mybestiole->jeTeVois(b));
}
void Membre::initCoords( int xLim, int yLim ){
    mybestiole->initCoords(xLim,yLim);
}
double Membre::getVisibilite() const{
    return(mybestiole->getVisibilite());
}
double Membre::getResist() const{
    return(mybestiole->getResist());
}
DBestiole* Membre::randomCloning() const{
    return(mybestiole->randomCloning());
}
bool Membre::vieillir(){
    return(mybestiole->vieillir());
}
void Membre::setExterne(DBestiole* p){
    mybestiole->setExterne(p);
}