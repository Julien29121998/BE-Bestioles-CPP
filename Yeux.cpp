#include "Yeux.h"

#include <cstdlib>
#include <cmath>
#include "Milieu.h"

void YeuxParams::Add(Param_Dict& pd)//Ajout de paramètres d'Yeux à un dictionnaire
{
    PushWith(string("Yeux"),pd);//Ajout des paramètre d'Yeux en tant que Paramètres
}

BParams* YeuxParams::cppm() const{//Copie des paramètres
   YeuxParams* p = new YeuxParams();
   p->delta=this->delta;
   p->gamma=this->gamma;
   p->alpha=this->alpha;
   return p;//Retour de paramètres identiques
}

Yeux::Yeux(DBestiole* dbestiole,double deltay, double gammay,double alpha)://Constructeur des yeux
Capteur(dbestiole,
((deltay>MAX_DELTA_Y)?MAX_DELTA_Y:((deltay<MIN_DELTA_Y)?MIN_DELTA_Y:deltay)),
((gammay>MAX_GAMMA_Y)?MAX_GAMMA_Y:((gammay<MIN_GAMMA_Y)?MIN_GAMMA_Y:gammay))),
alpha(((alpha>MAX_ALPHA)?MAX_ALPHA:((alpha<MIN_ALPHA)?MIN_ALPHA:alpha)))//Placement des valeurs dans les intervalles
{
   //cout<<"const Yeux"<<endl;
}     
Yeux::~Yeux()//Destructeur des yeux
{
   //cout<<"dest Yeux et ";

}
bool Yeux::dansAngle(const DBestiole* that) const{//La bestiole-cible est-elle dans l'angle
   paire_t myCoords= this->getCoords();//On récupère mes coordonnées
   paire_t itsCoords= that->getCoords();//on récupère ses coordonnées
   double x_vect = itsCoords.x-myCoords.x;//différence en x
   double y_vect = itsCoords.y-myCoords.y;//différence en y
   double norm_vect = sqrt(x_vect*x_vect + y_vect*y_vect);//distance
   double x_dir = cos(myCoords.ori);//vecteur direction: x
   double y_dir = sin(myCoords.ori);//vecteur direction: y
   double sc = (x_dir*x_vect+y_dir*y_vect)/norm_vect;//produit scalaire
   double arc = acos(sc);//arcos du produit scalaire = angle de la bestiole cible avec la direction de déplacement
   return(sc>0&&abs(arc)<(alpha/2));//la bestiole est devant ET dans l'angle
}
bool Yeux::jeTeVois(const DBestiole* b) const{//Vois-je la bestiole cible
   return((this->assezProche(b)&&this->assezEfficace(b)&&this->dansAngle(b))||Capteur::jeTeVois(b));//La bestiole est assez proche et je suis assez efficace et elle est dans l'angle OU je la vois autrement
}
DBestiole* Yeux::copy()//Copie des yeux
{
   return new Yeux(Capteur::copy(),delta, gamma,alpha);//renvoie une copie
}
void Yeux::draw( UImg & support )//Affichage des yeux
{
   Capteur::draw(support);//On dessine le reste
   paire_t coords = getCoords();//je récupère mes coordonnées
   double xty = coords.x + cos(coords.ori)*AFF_SIZE;//position à l'avant de la tête
   double yty = coords.y + sin(coords.ori)*AFF_SIZE;//position à l'avant de la tête
   double xd = -sin(coords.ori)*AFF_SIZE/3.5;//position des yeux orthogonalement par rapport à l'axe
   double yd = cos(coords.ori)*AFF_SIZE/3.5;//position des yeux orthogonalement par rapport à l'axe
   T blue[ 3 ];//bleu des yeux
   blue[0]=4;//bleu des yeux
   blue[1]=38;//bleu des yeux
   blue[2]=129;//bleu des yeux
   support.draw_circle(xty+xd,yty+yd,AFF_SIZE/4.,blue);//dessin des cercles des yeux
   support.draw_circle(xty-xd,yty-yd,AFF_SIZE/4.,blue);//dessin des cercles des yeux
}