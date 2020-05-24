#include "Bestiole.h"

#include <cstdlib>
#include <cmath>
#include "Milieu.h"

Bestiole::Bestiole(IComportement* comp): DBestiole()//constructeur de bestiole
{
   //cout << "const Bestiole par defaut" << endl;

   x = y = 0;//coordonnées
   cumulX = cumulY = 0.;//valeurs non entières des coordonnées
   orientation = static_cast<double>( rand() )/RAND_MAX*2.*M_PI;//orientation
   vitesse = static_cast<double>( rand() )/RAND_MAX*MAX_VITESSE;//vitesse
   esperance =static_cast<int>( 0.75*LIFE) + rand()%static_cast<int>(0.5*LIFE);//espérance de vie
   age=0;//age initial 0
   couleur = new T[ 3 ];//couleur aléatoire
   couleur[ 0 ] = static_cast<int>( static_cast<double>( rand() )/RAND_MAX*230. );//couleur aléatoire
   couleur[ 1 ] = static_cast<int>( static_cast<double>( rand() )/RAND_MAX*230. );//couleur aléatoire
   couleur[ 2 ] = static_cast<int>( static_cast<double>( rand() )/RAND_MAX*230. );//couleur aléatoire
   comportement=comp;//comportement
}
Bestiole::Bestiole(int _x, int _y,double _v, double _o, T* _couleur,IComportement* comp):DBestiole()
{//constructeur de bestiole spécifique
   //cout << "const Bestiole spécifique" << endl;
   x = _x;//coordonnées
   y = _y;//coordonnées
   cumulX = cumulY = 0.;//valeurs non entières des coordonnées
   orientation = _o;//orientation
   vitesse = _v;//vitesse
   esperance =static_cast<int>( 0.75*LIFE) + rand()%static_cast<int>(0.5*LIFE);//espérance de vie de la bestiole
   age=0;//age initial 0
   couleur = new T[ 3 ];//couleur identique à celle demandée
   memcpy( couleur,_couleur, 3*sizeof(T) );//couleur identique à celle demandée
   if(comp->isMultiple()){//Si le comportement est multiple ce n'est pas un flyweight
      comportement=new Multiple();//il est alors propre à l'instance
   }else{
      comportement=comp;//sinon c'est un flyweight, le même que tout le type.
   }

}


Bestiole::~Bestiole()//destructeur
{

   delete[] couleur;//on détruit la couleur
   if(comportement->isMultiple()){//si c'est un multiple, il faut le détruire car il dépend de l'instance
      delete comportement;
   }
   //cout << "dest Bestiole : ";

}


void Bestiole::initCoords( int xLim, int yLim )//initialisation aléatoire des coordonnées
{

   x = rand() % xLim;
   y = rand() % yLim;

}


void Bestiole::bouge(Milieu& monMilieu, double coef, paire_t objectif)//déplacement d'une bestiole
{
   int xLim=monMilieu.getWidth();//dans les limites du milieu
   int yLim=monMilieu.getHeight();//dans les limites du milieu
   double new_v=((objectif.vite>=sqrt(coef)*MAX_VITESSE)?sqrt(coef)*MAX_VITESSE:((objectif.vite>=0)?objectif.vite:0));//la vitesse désirée par la bestiole replacée dans l'intervalle permis par son corps
   new_v=(new_v-vitesse)*(PROPORTION_CHANGE)+vitesse;//sa future vitesse en considérant son inertie et son ancienne vitesse
   objectif.ori=fmod(objectif.ori,2*M_PI);//on se replace sur 0 2pi pour l'orientation
   orientation=fmod(orientation,2*M_PI);//on se replace sur 0 2pi pour l'orientation
   double new_or=objectif.ori-orientation;//différence d'orientation entre ce qui est voulu et ce qui est actuellement
   if(new_or>M_PI){//on détermine le chemin le plus court pour changer l'angle
      new_or=fmod((new_or-2*M_PI)*(PROPORTION_CHANGE),M_PI*2)+orientation;//sa future orientation en considérant son inertie et son ancienne orientation
   }
   else if(new_or<-M_PI){//on détermine le chemin le plus court pour changer l'angle
      new_or=fmod((new_or+2*M_PI)*(PROPORTION_CHANGE),M_PI*2)-M_PI*2+orientation;//sa future orientation en considérant son inertie et son ancienne orientation
   }
   else{//on détermine le chemin le plus court pour changer l'angle
      new_or=new_or*(PROPORTION_CHANGE)+orientation;//sa future orientation en considérant son inertie et son ancienne orientation
   }
   vitesse=new_v;//attribution des valeurs aux attributs
   orientation=new_or;//attribution des valeurs aux attributs

   double         nx, ny;//nouvelles coordonnées
   double         dx = cos( orientation )*vitesse;//déplacement
   double         dy = sin( orientation )*vitesse;//déplacement
   int            cx, cy;//partie non entière


   cx = static_cast<int>( cumulX ); cumulX -= cx;//partie non entière
   cy = static_cast<int>( cumulY ); cumulY -= cy;//partie non entière

   nx = x + dx + cx;//nouvelles coordonnées
   ny = y + dy + cy;//nouvelles coordonnées

   monMilieu.handleCollisions(this->coucheExterne);//gestion des collisions avec les autres bestioles réalisée par le milieu

   if ( (nx < 0) || (nx > xLim - 1) ) {//collision avec les bords
      orientation = M_PI - orientation;//rebond
      cumulX = 0.;
   }
   else {
      x = static_cast<int>( nx );//nouvelles coordonnées entières
      cumulX += nx - x;//nouvelle partie non entière
   }

   if ( (ny < 0) || (ny > yLim - 1) ) {//collision avec les bords
      orientation = -orientation;//rebond
      cumulY = 0.;
   }
   else {
      y = static_cast<int>( ny );//nouvelles coordonnées entières
      cumulY += ny - y;//nouvelle partie non entière
   }

}


void Bestiole::action( Milieu & monMilieu)//action de la bestiole
{
   (*this->comportement)(monMilieu,coucheExterne);//conséquence du comportement dans le milieu et en fonction de ses étages de décorateur
}


void Bestiole::draw( UImg & support )//dessiner une bestiole
{

   double         xt = x + cos( orientation )*AFF_SIZE/2.1;//position de la tête
   double         yt = y + sin( orientation )*AFF_SIZE/2.1;//position de la tête


   support.draw_ellipse( x, y, AFF_SIZE, AFF_SIZE/5., orientation/M_PI*180., couleur );//corps
   support.draw_circle( xt, yt, AFF_SIZE/2., couleur );//tête
   T* kindawhite = new T[ 3 ];//etiquette
   kindawhite[0]=241;//etiquette
   kindawhite[1]=241;//etiquette
   kindawhite[2]=241;//etiquette
   support.draw_text(x+AFF_SIZE,y+AFF_SIZE,this->coucheExterne->showID(),couleur,kindawhite,1,AFF_SIZE*1.618);//etiquette avec l'ID de la couche externe

}


bool Bestiole::jeTeVois( const DBestiole* b ) const//vois-je une autre créature
{
   return false;//sans organes non
}
double Bestiole::getVisibilite() const//suis je visible
{
   return 0;//sans organes oui
}
double Bestiole::getResist() const//suis je resistant
{
   return 1;//sans organes non
}
DBestiole* Bestiole::randomCloning() const{//clonage de la bestiole
   int invClone = static_cast<int>(1/CLONE_RATE);//tirage au hasard
   if(rand()%invClone==1){
   DBestiole* b = coucheExterne->copy();//copie de la bestiole en partant de l'extérieur et récursivement à travers les décorateurs vers l'intérieur.
   b->setExterne(b);//couche externe de la nouvelle bestiole
      return b;
   }
   else{
      return nullptr;//pas de clonage cette fois ci, pas de chance
   }
}
bool Bestiole::vieillir(){//vieillir
   age++;//l'age avance d'un
   if(age>=esperance){//si il a dépassé l'espérance on signale la bestiole pour suppression par le milieu
      return true;
   }
   return false;
}
DBestiole* Bestiole::copy(){//copie de la bestiole
   Bestiole* b = new Bestiole(
   this->x+(rand()%3-1)*AFF_SIZE,//variabilité des coordonnées
   this->y+(rand()%3-1)*AFF_SIZE,//variabilité des coordonnées
   this->vitesse*(0.92+0.16*(static_cast<double>(rand())/RAND_MAX)),//variabilité des coordonnées
   this->orientation*(0.92+0.16*(static_cast<double>(rand())/RAND_MAX)),//variabilité des coordonnées
   this->couleur,this->comportement);//la couleur et le comportement sont identiques
   b->setType(this->getType());//le type reste le même
   return b;//on utilise le constructeur paramétré puis en renvoie le resultat
}
void Bestiole::setExterne(DBestiole* p){//enseigner à une bestiole sa couche externe de décorateur
   coucheExterne= p;
}
paire_t Bestiole::getCoords() const{//getter des coordonnées
   paire_t res;
   res.x=this->x;
   res.y=this->y;
   res.ori=this->orientation;
   res.vite=this->vitesse;
   return res;
}
void Bestiole::killMe(){//tuer une bestiole revient à faire exploser son age pour être ramassée ensuite par le milieu et son système de destruction
   this->age+=this->esperance;
}

void Bestiole::setCoords(paire_t coords){//setter des coordonnées
   x=coords.x;
   y=coords.y;
   orientation=coords.ori;
   vitesse=coords.vite;
}
string Bestiole::getType() const{//getter du type
   return type;
}
void Bestiole::setType(string ntype){//setter du type
   this->type=ntype;
}