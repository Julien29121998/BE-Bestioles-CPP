#include "Nageoire.h"

#include <cstdlib>
#include <cmath>
#include "Milieu.h"

void NageoParams::Add(Param_Dict& pd)//Ajout des paramètres de nageoires au dictionnaire de paramètres
{
    PushWith(string("Nageoire"),pd);//Ajout en tant que paramètres
}

BParams* NageoParams::cppm() const{//Copie des paramètres de nageoires
   NageoParams* p = new NageoParams();
   p->nu=this->nu;
   return p;//retourne des paramètres
}
Nageoire::Nageoire(DBestiole* dbestiole,double nu):Membre(dbestiole),nu(((nu>MAX_NU)?MAX_NU:((nu<1)?1:nu)))//Constructeur de nageoires - on vérifie que les valeurs sont dans l'intervalle
{
   //cout<<"const Nageoire"<<endl;
}     
Nageoire::~Nageoire()//Destructeur Nageoire
{
   //cout<<"dest Nageoire et ";

}                              
void Nageoire::draw( UImg & support )//Dessiner les nageoires
{
   Membre::draw(support);//on dessine le reste
   paire_t coords = getCoords();//on récupère mes coordonnées
   T grey[ 3 ];//couleur grise
   grey[0]=92+38*(1-nu/MAX_NU);//gris dont l'intensité dépend de l'efficacité de la nageoire
   grey[1]=92+38*(1-nu/MAX_NU);//gris dont l'intensité dépend de l'efficacité de la nageoire
   grey[2]=92+38*(1-nu/MAX_NU);//gris dont l'intensité dépend de l'efficacité de la nageoire
   double xq = coords.x - cos( coords.ori)*AFF_SIZE/1.1;//bout du corps de la bestiole
   double yq = coords.y - sin( coords.ori)*AFF_SIZE/1.1;//bout du corps de la bestiole
   double xm = xq - cos( coords.ori)*AFF_SIZE/1.8;//longueur de la nageoire
   double ym = yq - sin( coords.ori)*AFF_SIZE/1.8;//longueur de la nageoire
   double xd = -sin(coords.ori)*AFF_SIZE/3.1;//largeur de la nageoire par rapport à l'axe
   double yd = cos(coords.ori)*AFF_SIZE/3.1;//largeur de la nageoire par rapport à l'axe
   support.draw_triangle(xq,yq,xm+xd,ym+yd,xm-xd,ym-yd,grey);//On dessine le triangle

}
void Nageoire::bouge(Milieu& monMilieu,double coef, paire_t objectif){//Bouger la Bestiole avec la nageoire
   Membre::bouge(monMilieu, nu * coef, objectif);//déplacement normal, multiplié par le facteur de la nageoire
}

DBestiole* Nageoire::copy()//copier la nageoire
{
   return new Nageoire(Membre::copy(),nu);//on renvoie la nouvelle nageoire
}