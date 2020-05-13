#include "Bestiole.h"

#include <cstdlib>
#include <cmath>
#include "Milieu.h"

Bestiole::Bestiole(): DBestiole()
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

}
Bestiole::Bestiole(int _x, int _y,double _v, double _o, T* _couleur):DBestiole()
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

}


Bestiole::~Bestiole()
{

   delete[] couleur;

   cout << "dest Bestiole" << endl;

}


void Bestiole::initCoords( int xLim, int yLim )
{

   x = rand() % xLim;
   y = rand() % yLim;

}


void Bestiole::bouge( int xLim, int yLim, double coef )
{

   double         nx, ny;
   double         dx = cos( orientation )*vitesse;
   double         dy = -sin( orientation )*vitesse;
   int            cx, cy;


   cx = static_cast<int>( cumulX ); cumulX -= cx;
   cy = static_cast<int>( cumulY ); cumulY -= cy;

   nx = x + dx + cx;
   ny = y + dy + cy;

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

   bouge( monMilieu.getWidth(), monMilieu.getHeight(),1 );

}


void Bestiole::draw( UImg & support )
{

   double         xt = x + cos( orientation )*AFF_SIZE/2.1;
   double         yt = y - sin( orientation )*AFF_SIZE/2.1;


   support.draw_ellipse( x, y, AFF_SIZE, AFF_SIZE/5., -orientation/M_PI*180., couleur );
   support.draw_circle( xt, yt, AFF_SIZE/2., couleur );
   T* kindawhite = new T[ 3 ];
   kindawhite[0]=241;
   kindawhite[1]=241;
   kindawhite[2]=241;
   support.draw_text(x+AFF_SIZE,y+AFF_SIZE,this->showID(),couleur,kindawhite,1,AFF_SIZE*1.618);

}


bool Bestiole::jeTeVois( const DBestiole* b ) const
{

   //double         dist;
   //dist = std::sqrt( (x-b.x)*(x-b.x) + (y-b.y)*(y-b.y) );
   //return ( dist <= LIMITE_VUE );----> ancien code, à placer dans la focntion d'évaluation de distance des capteurs
   return false;
}
double Bestiole::getVisibilite() const
{
   return 0;
}
double Bestiole::getResist() const
{
   return 0;
}
DBestiole* Bestiole::randomCloning() const{
   if(rand()%CLONE_RATE==1){
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
      delete coucheExterne;
      return true;
   }
   return false;
}
DBestiole* Bestiole::copy(){
   return new Bestiole(this->x,this->y,this->vitesse,this->orientation,this->couleur);
}
void Bestiole::setExterne(DBestiole* p){
   coucheExterne= p;
}
paire_t Bestiole::getCoords() const{
   paire_t res;
   res.x=this->x;
   res.y=this->y;
   return res;
}