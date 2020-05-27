#include "Carapace.h"

#include <cstdlib>
#include <cmath>
#include "Milieu.h"

void CaraParams::Add(Param_Dict& pd)//Ajouter ces paramètres de carapace à un dictionnaire de paramètres
{
    PushWith(string("Carapace"),pd);//ajout
}

BParams* CaraParams::cppm() const{//copie
   CaraParams* p = new CaraParams();
   p->omega=this->omega;
   p->eta=this->eta;
   return p;//retour d'un nouvel objet copié
}

Carapace::Carapace(DBestiole* dbestiole,double omega, double eta):Membre(dbestiole),//constructeur
omega(((omega>MAX_OMEGA)?MAX_OMEGA:((omega<1)?1:omega))),
eta(((eta>MAX_ETA)?MAX_ETA:((eta<1)?1:eta)))//on place les valeurs dans les intervalles
{
   //cout<<"const Carapace"<<endl;
}     
Carapace::~Carapace()
{
   //cout<<"dest Carapace et ";

}                              
void Carapace::draw( UImg & support )//dessiner une carapace
{
   Membre::draw(support);//on dessine le reste
   paire_t coords = getCoords();//ma position
   T lightbrown[ 3 ];//brun
   lightbrown[0]=150-38*(omega/MAX_OMEGA);//brun d'intensité variant selon l'efficacité
   lightbrown[1]=112;//brun d'intensité variant selon l'efficacité
   lightbrown[2]=22+60*(1-(eta/MAX_ETA));//brun d'intensité variant selon l'efficacité
   support.draw_circle(coords.x,coords.y,AFF_SIZE/2.3,lightbrown);//dessiner un cercle

}
double Carapace::getResist()const{//Resistance avec une carapace
   return omega*Membre::getResist();//Resistance de base*Resistance avec une carapace
}
void Carapace::bouge(Milieu& monMilieu,double coef, paire_t objectif){//vitesse avec une carapace
   Membre::bouge(monMilieu, coef/eta, objectif);//vitesse réduite par la carapace
}

DBestiole* Carapace::copy()//copier la carapace
{
   return new Carapace(Membre::copy(),omega, eta);
}