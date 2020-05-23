#include "Milieu.h"
#include "Factory.h"
#include "Comportement.h"
#include "Interpreter.h"

#include <cstdlib>
#include <vector>
#include <cmath>
#include <ctime>
#include <fstream>
#define __END__CSV "\\END__CSV"

const T    Milieu::white[] = { (T)255, (T)255, (T)255 };


Milieu::Milieu( int _width, int _height, int target_population ) : UImg( _width, _height, 1, 3 ),
                                            width(_width), height(_height)
{
   IComportement* dumb = new Dumb();
   IComportement* peureuse = new Peureuse();
   IComportement* kamikaze = new Kamikaze();
   IComportement* prevoyante = new Prevoyante();
   IComportement* gregaire= new Gregaire();
   Comportements_Disponibles=std::vector<IComportement*>(4,NULL);
   Comportements_Disponibles[COMP_PEUREUSE]=(peureuse);
   Comportements_Disponibles[COMP_KAMIKAZE]=(kamikaze);
   Comportements_Disponibles[COMP_PREVOYANTE]=(prevoyante);
   Comportements_Disponibles[COMP_GREGAIRE]=(gregaire);
   Comportement_par_defaut = dumb;
   cout << "const Milieu" << endl;
   this->target_pop=target_population;
   std::srand( time(NULL) );
   timer=0;
}


Milieu::~Milieu()
{
   for ( std::vector<DBestiole*>::iterator it = listeBestioles.begin() ; it != listeBestioles.end() ; ++it )
   {

      delete (*it);

   }
   for(std::vector<IComportement*>::iterator cit=Comportements_Disponibles.begin();cit!=Comportements_Disponibles.end();++cit){
      delete(*cit);
   }
   delete(Comportement_par_defaut);
   cout << "dest Milieu" << endl;

}


void Milieu::step(std::vector<Factory> nf)
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
      DBestiole* newborn = (*it)->randomCloning();
      if(newborn!=nullptr){
         toAdd.push_back(newborn);
      }
      if((*it)->vieillir()){
         toDelete.push_back(it-beginit);
      }

   }
   if(!nf.empty()){
      for(auto cf=nf.begin();cf!=nf.end();++cf){
         cf->fillWith(toAdd,static_cast<int>(cf->proportion),*this);
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
         it->fillWith(toAdd,static_cast<int>(taux),*this);
      }
   }
   for ( std::vector<DBestiole*>::iterator a_it = toAdd.begin() ; a_it != toAdd.end() ; ++a_it )
   {
      listeBestioles.push_back(*a_it);
   }
   toAdd.erase(toAdd.begin(),toAdd.end());
   if(timer%10==0){
      std::ofstream output;
      std::ifstream header_read;
      std::string line,word;
      int found;
      output.open (Interpreter::OutputFile, std::ios::app);
      output<<timer<<",";
      header_read.open(Interpreter::OutputFile);
      getline(header_read,line);
      line=line+__END__CSV;
      header_read.close();
      auto contenu = this->contenu();
      found = line.find(","),word=line.substr(0,found), line=line.substr(found+1,line.size());
      while(found = line.find(","),word=line.substr(0,found), line=line.substr(found+1,line.size()),word!=__END__CSV){
         output<<contenu.find(word)->second<<",";
      }
      output<<endl;
      output.close();
   }
   timer++;
}


int Milieu::nbVoisins( const DBestiole*  b )
{

   int nb = 0;
   for ( std::vector<DBestiole*>::iterator it = listeBestioles.begin() ; it != listeBestioles.end() ; ++it ){
      if ( !(b == *it) && b->jeTeVois(*it)) {
         ++nb;
      }
   }

   return nb;

}
std::vector<DBestiole*> Milieu::QuiVoisJe( const DBestiole* b)
{
   std::vector<DBestiole*> ans;
   for ( std::vector<DBestiole*>::iterator it = listeBestioles.begin() ; it != listeBestioles.end() ; ++it ){
      if ( !(b == *it) && b->jeTeVois(*it)) {
         ans.push_back(*it);
      }
   }
   return ans;
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
      it->fillWith(listeBestioles,static_cast<int>(it->proportion*target_pop),*this);
   }
}
void Milieu::handleCollisions(DBestiole* b){
   paire_t myCoords = b->getCoords();

   for(std::vector<DBestiole*>::iterator it = listeBestioles.begin() ; it != listeBestioles.end() ; ++it){
      paire_t theirCoords = (*it)->getCoords();
      double deltx=theirCoords.x-myCoords.x;
      double delty=theirCoords.y-myCoords.y;
      double norm = std::sqrt(deltx*deltx+delty*delty);
      if((norm<DBestiole::AFF_SIZE)
      &&((deltx*std::cos(myCoords.ori)
      +delty*std::sin(myCoords.ori))>0)
      &&(b->identite!=(*it)->identite)){  
         myCoords.ori=-myCoords.ori;
         theirCoords.ori=-theirCoords.ori;
         double transition=myCoords.vite;
         myCoords.vite=theirCoords.vite;
         theirCoords.vite=transition;
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
int Milieu::Count() const{
   return listeBestioles.size();
}
void Milieu::describeMe() const{
   cout<<"Milieu :"<<endl;
   for(auto b=listeBestioles.begin();b!=listeBestioles.end();++b){
      cout<<(*b)->getType()<<endl;
   }
}
std::map<std::string,int> Milieu::contenu() const{
   std::map<std::string,int> ans;
   for(auto lf=listeFactories.begin();lf!=listeFactories.end();++lf){
      ans.emplace(make_pair(lf->getTypeName(),0));
   }
   ans.emplace(make_pair(Interpreter::Others,0));
   for(auto b=listeBestioles.begin();b!=listeBestioles.end();++b){
      auto k = ans.find((*b)->getType());
      if(k==ans.end()){
         k=ans.find(Interpreter::Others);
      }
      k->second+=1;
   }
   return ans;
}
