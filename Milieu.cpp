#include "Milieu.h"
#include "Factory.h"

#include <cstdlib>
#include <cmath>
#include <ctime>


const T    Milieu::white[] = { (T)255, (T)255, (T)255 };


Milieu::Milieu( int _width, int _height, int target_population ) : UImg( _width, _height, 1, 3 ),
                                            width(_width), height(_height)
{

   cout << "const Milieu" << endl;
   this->target_pop=target_population;
   std::srand( time(NULL) );

}


Milieu::~Milieu()
{
   for ( std::vector<DBestiole*>::iterator it = listeBestioles.begin() ; it != listeBestioles.end() ; ++it )
   {

      delete (*it);

   }
   cout << "dest Milieu" << endl;

}


void Milieu::step()
{
   int pos, diff;
   std::vector<int> toDelete;
   std::vector<DBestiole*> toAdd;
   cimg_forXY( *this, x, y ) fillC( x, y, 0, white[0], white[1], white[2] );
   std::vector<DBestiole*>::iterator beginit = listeBestioles.begin();
   for ( std::vector<DBestiole*>::iterator it = beginit ; it != listeBestioles.end() ; ++it )
   {
      
      (*it)->action( *this);
      (*it)->draw( *this );
      this->nbVoisins(*it);
      DBestiole* newborn = (*it)->randomCloning();
      if(newborn!=nullptr){
         toAdd.push_back(newborn);
      }
      if((*it)->vieillir()){
         toDelete.push_back(it-beginit);
      }

   }
   pos=0;
   for(std::vector<DBestiole*>::iterator t_it = beginit;t_it!=listeBestioles.end();++t_it){
      if(find(toDelete.begin(),toDelete.end(),pos++)==toDelete.end()){
         toAdd.push_back(*t_it);
      }
      else{
         delete *t_it;
      }
   }
   toDelete.erase(toDelete.begin(),toDelete.end());
   listeBestioles.erase(beginit,listeBestioles.end());
   diff =target_pop-toAdd.size();
   if(diff>0){
      for(auto it=listeFactories.begin();it!=listeFactories.end();++it){
         double r =(static_cast<double>(std::rand()) / (RAND_MAX));
         double taux = (it->proportion)*diff*r*DBestiole::GENERATION_RATE;
         it->fillWith(toAdd,static_cast<int>(taux),width,height);
      }
   }
   for ( std::vector<DBestiole*>::iterator a_it = toAdd.begin() ; a_it != toAdd.end() ; ++a_it )
   {
      listeBestioles.push_back(*a_it);
   }
   toAdd.erase(toAdd.begin(),toAdd.end());

}


int Milieu::nbVoisins( const DBestiole*  b )
{

   int         nb = 0;


   for ( std::vector<DBestiole*>::iterator it = listeBestioles.begin() ; it != listeBestioles.end() ; ++it )
      if ( !(b == *it) && b->jeTeVois(*it)) {
         cout<<b->showID()<<" voit "<<(*it)->showID()<<endl;
         ++nb;
      }

   return nb;

}

void Milieu::kill(int id){
   for(std::vector<DBestiole*>::iterator it = listeBestioles.begin() ; it != listeBestioles.end() ; ++it){
      if(((*it)->identite)==id){
         (*it)->killMe();
      }
   }
}
void Milieu::introduire(){
   for(auto it=listeFactories.begin();it!=listeFactories.end();++it){
      it->fillWith(listeBestioles,static_cast<int>(it->proportion*target_pop),width,height);
   }
}
void Milieu::handleCollisions(DBestiole* b){

   auto norm=[](double a, double b){return std::sqrt(a*a+b*b);};
   auto custom_atan= [](double x, double y)
     {if(x!=0)return((x<0?M_PI:(y<0?2*M_PI:0))+((x*y)>0?1:-1)*std::atan(std::abs(y/x)));
      else return((y>0?1:-1)*M_PI/2);};

   paire_t myCoords = b->getCoords();
   xcoords_t myDCoords = b->getDoubleCoords();

   for(std::vector<DBestiole*>::iterator it = listeBestioles.begin() ; it != listeBestioles.end() ; ++it){
      
      paire_t theirCoords = (*it)->getCoords();
      xcoords_t theirDCoords =(*it)->getDoubleCoords();

      double deltx=(theirDCoords.x-myDCoords.x);
      double delty=(theirDCoords.y-myDCoords.y);

      double xv=myCoords.vite*std::cos(myCoords.ori);
      double yv=myCoords.vite*std::sin(myCoords.ori);

      double norm_delt=norm(deltx,delty);
      if((norm_delt<DBestiole::AFF_SIZE)&&(b->identite!=(*it)->identite)){  
         if(norm_delt==0){norm_delt=0.01;}
         
         double xv2=theirCoords.vite*std::cos(myCoords.ori);
         double yv2=theirCoords.vite*std::sin(myCoords.ori);

         double v_b_vers_it=(xv*deltx+yv*delty)/norm_delt;
         double v_it_vers_b=-(xv2*deltx+yv2*delty)/norm_delt;

         double vxnormal_b = (delty/norm_delt)*v_it_vers_b;
         double vynormal_b = -(deltx/norm_delt)*v_it_vers_b;
         double vxnormal_it = (delty/norm_delt)*v_b_vers_it;
         double vynormal_it = -(deltx/norm_delt)*v_b_vers_it;

         double nouvelle_vitesse_x_b=xv-vxnormal_it+vxnormal_b;
         double nouvelle_vitesse_y_b=yv-vynormal_it+vynormal_b;
         double nouvelle_vitesse_x_it=xv2-vxnormal_b+vxnormal_it;
         double nouvelle_vitesse_y_it=yv2-vynormal_b+vynormal_it;
         
         myCoords.ori=custom_atan(nouvelle_vitesse_x_b,nouvelle_vitesse_y_b);
         myCoords.vite=norm(nouvelle_vitesse_x_b,nouvelle_vitesse_y_b);
         theirCoords.ori=custom_atan(nouvelle_vitesse_x_it,nouvelle_vitesse_y_it);
         theirCoords.vite=norm(nouvelle_vitesse_x_it,nouvelle_vitesse_y_it);

         b->setCoords(myCoords);
         (*it)->setCoords(theirCoords);

         if((static_cast<double>(std::rand())/RAND_MAX)/(b->getResist())>=DBestiole::SURVIVE_COLLISION){
            b->killMe();
         }
         if((static_cast<double>(std::rand())/RAND_MAX)/((*it)->getResist())>=DBestiole::SURVIVE_COLLISION){
            (*it)->killMe();
         }
      }
   }
}