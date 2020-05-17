#include "Bestiole.h"

#include <cstdlib>
#include <cmath>
#include "Milieu.h"

Bestiole::Bestiole(IComportement* comp): DBestiole()
{
   cout << "const Bestiole par defaut" << endl;

   x = y = 0;
   cumulX = cumulY = 0.;
   orientation = static_cast<double>( rand() )/RAND_MAX*2.*M_PI;
   vitesse = static_cast<double>( rand() )/RAND_MAX*MAX_VITESSE;
   esperance =static_cast<int>( 0.6667*LIFE) + rand()%static_cast<int>(0.3333*LIFE);
   age=0;
   couleur = new T[ 3 ];
   couleur[ 0 ] = static_cast<int>( static_cast<double>( rand() )/RAND_MAX*230. );
   couleur[ 1 ] = static_cast<int>( static_cast<double>( rand() )/RAND_MAX*230. );
   couleur[ 2 ] = static_cast<int>( static_cast<double>( rand() )/RAND_MAX*230. );
   if(comp->isMultiple()){
      comportement=new Multiple();
   }else{
      comportement=comp;
   }
}
Bestiole::Bestiole(int _x, int _y,double _v, double _o, T* _couleur,IComportement* comp):DBestiole()
{
   cout << "const Bestiole spécifique" << endl;
   x = _x;
   y = _y;
   cumulX = cumulY = 0.;
   orientation = _o;
   vitesse = _v;
   esperance =static_cast<int>( 0.75*LIFE) + rand()%static_cast<int>(0.5*LIFE);
   age=0;
   couleur = new T[ 3 ];
   memcpy( couleur,_couleur, 3*sizeof(T) );
   if(comp->isMultiple()){
      comportement=new Multiple();
   }else{
      comportement=comp;
   }

}


Bestiole::~Bestiole()
{

   delete[] couleur;
   if(comportement->isMultiple()){
      delete comportement;
   }
   cout << "dest Bestiole : ";

}


void Bestiole::initCoords( int xLim, int yLim )
{

   x = rand() % xLim;
   y = rand() % yLim;

}


void Bestiole::bouge(Milieu& monMilieu, double coef )
{
   int xLim=monMilieu.getWidth();
   int yLim=monMilieu.getHeight();
   vitesse=((vitesse>=sqrt(coef)*MAX_VITESSE)?sqrt(coef)*MAX_VITESSE:vitesse);

   double         nx, ny;
   double         dx = cos( orientation )*vitesse;
   double         dy = sin( orientation )*vitesse;
   int            cx, cy;


   cx = static_cast<int>( cumulX ); cumulX -= cx;
   cy = static_cast<int>( cumulY ); cumulY -= cy;

   nx = x + dx + cx;
   ny = y + dy + cy;

   monMilieu.handleCollisions(this->coucheExterne);
   if ( (nx < 0) || (nx > xLim - 1) ) {
      orientation = M_PI - orientation;
      cumulX = 0.;
   }
   else {
      x = static_cast<int>( nx );
      cumulX += nx - x;
   }

   if ( (ny < 0) || (ny > yLim - 1) ) {
      orientation = -orientation;
      cumulY = 0.;
   }
   else {
      y = static_cast<int>( ny );
      cumulY += ny - y;
   }

}


void Bestiole::action( Milieu & monMilieu)
{
   (*this->comportement)(monMilieu,coucheExterne);
   coucheExterne->bouge( monMilieu,1. );

}


void Bestiole::draw( UImg & support )
{

   double         xt = x + cos( orientation )*AFF_SIZE/2.1;
   double         yt = y + sin( orientation )*AFF_SIZE/2.1;


   support.draw_ellipse( x, y, AFF_SIZE, AFF_SIZE/5., orientation/M_PI*180., couleur );
   support.draw_circle( xt, yt, AFF_SIZE/2., couleur );
   T* kindawhite = new T[ 3 ];
   kindawhite[0]=241;
   kindawhite[1]=241;
   kindawhite[2]=241;
   support.draw_text(x+AFF_SIZE,y+AFF_SIZE,this->coucheExterne->showID(),couleur,kindawhite,1,AFF_SIZE*1.618);

}


bool Bestiole::jeTeVois( const DBestiole* b ) const
{
   return false;
}
double Bestiole::getVisibilite() const
{
   return 0;
}
double Bestiole::getResist() const
{
   return 1;
}
DBestiole* Bestiole::randomCloning() const{
   int invClone = static_cast<int>(1/CLONE_RATE);
   if(rand()%invClone==1){
   DBestiole* b = coucheExterne->copy();
   b->setExterne(b);
      return b;
   }
   else{
      return nullptr;
   }
}
bool Bestiole::vieillir(){
   age++;
   if(age>=esperance){
      return true;
   }
   return false;
}
DBestiole* Bestiole::copy(){
   return new Bestiole(
   this->x+(rand()%3-1)*AFF_SIZE,
   this->y+(rand()%3-1)*AFF_SIZE,
   this->vitesse*(0.92+0.16*(static_cast<double>(rand())/RAND_MAX)),
   this->orientation*(0.92+0.16*(static_cast<double>(rand())/RAND_MAX)),
   this->couleur,this->comportement);
}
void Bestiole::setExterne(DBestiole* p){
   coucheExterne= p;
}
paire_t Bestiole::getCoords() const{
   paire_t res;
   res.x=this->x;
   res.y=this->y;
   res.ori=this->orientation;
   res.vite=this->vitesse;
   return res;
}
void Bestiole::killMe(){
   this->age+=this->esperance;
}

void Bestiole::setCoords(paire_t coords){
   x=coords.x;
   y=coords.y;
   orientation=coords.ori;
   vitesse=coords.vite;
}
