#include "Oreilles.h"

#include <cstdlib>
#include <cmath>
#include "Milieu.h"

void OreParams::Add(Param_Dict& pd)//Ajouter les paramètres d'oreilles à un dictionnaire de paramètres
{
    PushWith(string("Oreilles"),pd);//Ajouter au dictionnaire en tant que paramètre
}

BParams* OreParams::cppm() const{//Copie des paramètres d'oreilles
   OreParams* p = new OreParams();
   p->delta=this->delta;
   p->gamma=this->gamma;
   return p;//on retourne les paramètres
}

Oreilles::Oreilles(DBestiole* dbestiole,double deltao, double gammao)://Constructeur d'oreilles
Capteur(dbestiole,
((deltao>MAX_DELTA_O)?MAX_DELTA_O:((deltao<MIN_DELTA_O)?MIN_DELTA_O:deltao)),
((gammao>MAX_GAMMA_O)?MAX_GAMMA_O:((gammao<MIN_GAMMA_O)?MIN_GAMMA_O:gammao)))//On force les valeurs dans les intervalles
{
   //cout<<"const Oreilles"<<endl;
}     
Oreilles::~Oreilles()//Destructeur
{
   //cout<<"dest Oreilles et ";

}                              
bool Oreilles::jeTeVois(const DBestiole* b) const{//Perçois-je cette bestiole ?
   return((this->assezProche(b)&&this->assezEfficace(b))||Capteur::jeTeVois(b));//elle est assez proche et je suis assez efficace OU je la perçois autrement
}
DBestiole* Oreilles::copy()//copier les oreilles
{
   return new Oreilles(Capteur::copy(),delta, gamma);//crée une copie des oreilles
}
void Oreilles::draw( UImg & support )//dessiner les oreilles
{
   Capteur::draw(support);//on dessine le reste
   paire_t coords = getCoords();//On récpère mes coordonnées
   double xt = coords.x + cos(coords.ori)*AFF_SIZE/2.1;//coordonées de la tête
   double yt = coords.y + sin(coords.ori)*AFF_SIZE/2.1;//coordonées de la tête
   double xd = -sin(coords.ori)*AFF_SIZE/1.8;//position normale par rapport à l'axe de la bestiole
   double yd = cos(coords.ori)*AFF_SIZE/1.8;//position normale par rapport à l'axe de la bestiole
   T red[ 3 ];//Couleur rouge des oreilles
   red[0]=182;//Couleur rouge des oreilles
   red[1]=10;//Couleur rouge des oreilles
   red[2]=10;//Couleur rouge des oreilles
   support.draw_circle(xt+xd,yt+yd,AFF_SIZE/3.7,red);//cercle des oreilles
   support.draw_circle(xt-xd,yt-yd,AFF_SIZE/3.7,red);//cercle des oreilles
}