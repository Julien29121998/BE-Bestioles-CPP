#include "Milieu.h"

#include <cstdlib>
#include <ctime>


const T    Milieu::white[] = { (T)255, (T)255, (T)255 };


Milieu::Milieu( int _width, int _height ) : UImg( _width, _height, 1, 3 ),
                                            width(_width), height(_height)
{

   cout << "const Milieu" << endl;

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
   int pos;
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

void Milieu::Introduire(int combien, BestiolesParams params){
   for(int i=0; i<combien;i++){
      DBestiole* bo = new Bestiole();
      DBestiole* lowest_layer = bo;
      if(params.camo!=NULL){
         bo = new Camouflages(bo,params.camo->phi);
      }
      if(params.nag!=NULL){
         bo = new Nageoire(bo,params.nag->nu);
      }
      if(params.cara!=NULL){
         bo = new Carapace(bo,params.cara->omega,params.cara->eta);
      }
      if(params.orei!=NULL){
         bo = new Oreilles(bo,params.orei->delta,params.orei->gamma);
      }
      if(params.yeux!=NULL){
         bo = new Yeux(bo,params.yeux->delta,params.yeux->gamma,params.yeux->alpha);
      }
      lowest_layer->setExterne(bo);
      this->addMember(bo);
   }
}
