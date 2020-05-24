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

const T    Milieu::white[] = { (T)255, (T)255, (T)255 };//blanc


Milieu::Milieu( int _width, int _height, int target_population ) : UImg( _width, _height, 1, 3 ),
                                            width(_width), height(_height)//constructeur du milieu
{
   IComportement* dumb = new Dumb();//On initialise les comportements flyweight
   IComportement* peureuse = new Peureuse();//On initialise les comportements flyweight
   IComportement* kamikaze = new Kamikaze();//On initialise les comportements flyweight
   IComportement* prevoyante = new Prevoyante();//On initialise les comportements flyweight
   IComportement* gregaire= new Gregaire();//On initialise les comportements flyweight
   Comportements_Disponibles=std::vector<IComportement*>(4,NULL);//Liste des comportements disponibles
   Comportements_Disponibles[COMP_PEUREUSE]=(peureuse);//Peureuse
   Comportements_Disponibles[COMP_KAMIKAZE]=(kamikaze);//Kamikaze
   Comportements_Disponibles[COMP_PREVOYANTE]=(prevoyante);//Prevoyante
   Comportements_Disponibles[COMP_GREGAIRE]=(gregaire);//Gregaire
   Comportement_par_defaut = dumb;//Comportement par défaut - Dumb
   //cout << "const Milieu" << endl;
   this->target_pop=target_population;//Population visée
   std::srand( time(NULL) );//Initialisation du générateur de valeurs aléatoires
   timer=0;//origine des temps
}


Milieu::~Milieu()//destructeur de milieu
{
   for ( std::vector<DBestiole*>::iterator it = listeBestioles.begin() ; it != listeBestioles.end() ; ++it )
   {//On detruit toutes les bestioles

      delete (*it);

   }
   for(std::vector<IComportement*>::iterator cit=Comportements_Disponibles.begin();cit!=Comportements_Disponibles.end();++cit){
      delete(*cit);//On detruit tous les comportements flyweight
   }
   delete(Comportement_par_defaut);//Destruction du comportement par défaut
   //cout << "dest Milieu" << endl;

}


void Milieu::step(std::vector<Factory> nf)//Epoque de la simulation
{
   int pos, diff;//positions; différence avec la population visée
   std::vector<int> toDelete;//position des bestioles à supprimer
   std::vector<DBestiole*> toAdd;//bestioles à ajouter
   cimg_forXY( *this, x, y ) fillC( x, y, 0, white[0], white[1], white[2] );//réinitialiser l'affichage entre chaque époque
   std::vector<DBestiole*>::iterator beginit = listeBestioles.begin();//position initiale
   for ( std::vector<DBestiole*>::iterator it = beginit ; it != listeBestioles.end() ; ++it )//pour chaque bestiole
   {
      
      (*it)->action( *this);//la bestiole agit
      (*it)->draw( *this );//dessiner la bestiole
      DBestiole* newborn = (*it)->randomCloning();//clonage potentiel
      if(newborn!=nullptr){
         toAdd.push_back(newborn);//on ajoute le clone si le clonage a eu lieu
      }
      if((*it)->vieillir()){//la bestiole vieillit et si besoin, elle meurt
         toDelete.push_back(it-beginit);//pour la faire mourir, on l'ajoute à la liste des bestioles à supprimer
      }

   }
   if(!nf.empty()){//si l'utilisateur a créé au moins une factory avec une commande
      for(auto cf=nf.begin();cf!=nf.end();++cf){
         cf->fillWith(toAdd,static_cast<int>(cf->proportion),*this);//on ajoute les bestioles voulues pour chaque factory
      }
   }
   pos=0;//on se place sur la première bestiole de la liste des bestioles
   for(std::vector<DBestiole*>::iterator t_it = beginit;t_it!=listeBestioles.end();++t_it){//Pour toutes les bestioles
      if(find(toDelete.begin(),toDelete.end(),pos++)==toDelete.end()){//Si la position de la bestiole n'est pas une position à supprimer
         toAdd.push_back(*t_it);//on ajoute cette bestiole à la liste des bestioles pour l'époque suivante
      }
      else{//si jamais il faut supprimer la bestiole
         delete *t_it;//on la supprime
      }
   }
   toDelete.erase(toDelete.begin(),toDelete.end());//On efface la liste des bestioles à supprimer
   listeBestioles.erase(beginit,listeBestioles.end());//On efface la liste des bestioles de l'époque qui vient de s'achever
   diff =target_pop-toAdd.size();//on évalue la différence par rapport à la population visée
   if(diff>0){//si il en manque
      for(auto it=listeFactories.begin();it!=listeFactories.end();++it){//on solicite toutes les factories
         double r =(static_cast<double>(std::rand()) / (RAND_MAX));//on tire au hasard si on va l'activer
         double taux = (it->proportion)*diff*r*DBestiole::GENERATION_RATE;//on calcule le taux manquant à regénérer
         it->fillWith(toAdd,static_cast<int>(taux),*this);//On remplit le nombre de bestioles à rajouter
      }
   }
   for ( std::vector<DBestiole*>::iterator a_it = toAdd.begin() ; a_it != toAdd.end() ; ++a_it )//pour toutes les bestioles à ajouter 
   {
      listeBestioles.push_back(*a_it);//on ajoute ces bestioles dans la liste de l'époque suivante
   }
   toAdd.erase(toAdd.begin(),toAdd.end());//on efface la liste temporaire
   if(timer%10==0){//si on est à une époque multiple de 10
      std::ofstream output;//on prépare un flux de sortie
      std::ifstream header_read;//on prépare un flux de lecture
      std::string line,word;//strings de lecture
      int found;//position de la colonne du csv dans laquelle on va écrire
      output.open (Interpreter::OutputFile, std::ios::app);//on ouvre le fichier de sortie
      output<<timer<<",";//on écrit l'époque d'abord
      header_read.open(Interpreter::OutputFile);//on lit le fichier
      getline(header_read,line);//on consulte la ligne des headers de colonnes
      line=line+__END__CSV;//on ajoute un marqueur de fin de ligne
      header_read.close();//on ferme le fichier
      auto contenu = this->contenu();//on liste les types de bestioles et leurs effectifs dans la simulation
      found = line.find(","),word=line.substr(0,found), line=line.substr(found+1,line.size());//on coupe le premier mot, header du temps
      while(found = line.find(","),word=line.substr(0,found), line=line.substr(found+1,line.size()),word!=__END__CSV){//pour tous les headers
         output<<contenu.find(word)->second<<",";//on écrit l'effectif au bas de la bonne colonne
      }
      output<<endl;//on retourne à la ligne
      output.close();//on ferme le flux de sortie
   }
   timer++;//date suivante
}


int Milieu::nbVoisins( const DBestiole*  b )//compter les voisins visibles d'une bestiole dans le milieu
{

   int nb = 0;//compteur à 0
   for ( std::vector<DBestiole*>::iterator it = listeBestioles.begin() ; it != listeBestioles.end() ; ++it ){
      if ( !(b == *it) && b->jeTeVois(*it)) {//pour toutes les bestioles, si la bestiole la voit
         ++nb;//on incrémente le compte
      }
   }

   return nb;//on renvoie le compte

}
std::vector<DBestiole*> Milieu::QuiVoisJe( const DBestiole* b)//lister les voisins visibles d'une bestiole dans le milieu
{
   std::vector<DBestiole*> ans;//liste vide
   for ( std::vector<DBestiole*>::iterator it = listeBestioles.begin() ; it != listeBestioles.end() ; ++it ){
      if ( !(b == *it) && b->jeTeVois(*it)) {//pour toutes les bestioles, si la bestiole la voit
         ans.push_back(*it);//on l'ajoute
      }
   }
   return ans;//on renvoie la liste
}

void Milieu::kill(int id){//tuer une bestiole d'id donné
   for(std::vector<DBestiole*>::iterator it = listeBestioles.begin() ; it != listeBestioles.end() ; ++it){
      if(((*it)->identite)==id){//pour toutes les bestioles, si elle a l'identité cherchée
         (*it)->killMe();//on la tue
      }
   }
}
void Milieu::introduire(){//On ajoute au milieu des bestioles suivant les factories
   for(auto it=listeFactories.begin();it!=listeFactories.end();++it){
      it->fillWith(listeBestioles,static_cast<int>(it->proportion*target_pop),*this);//pour toutes les factories, on remplit la liste de la simulation correctement
   }
}
void Milieu::handleCollisions(DBestiole* b){//gérer les collisions avec une bestiole donnée
   paire_t myCoords = b->getCoords();//on récupère les coordonnées de la bestiole

   for(std::vector<DBestiole*>::iterator it = listeBestioles.begin() ; it != listeBestioles.end() ; ++it){//pour toutes les bestioles
      paire_t theirCoords = (*it)->getCoords();//on récupère les coordonnées
      double deltx=theirCoords.x-myCoords.x;//différence de coordonnées
      double delty=theirCoords.y-myCoords.y;//différence de coordonnées
      double norm = std::sqrt(deltx*deltx+delty*delty);//norme de la distance
      if((norm<DBestiole::AFF_SIZE)
      &&((deltx*std::cos(myCoords.ori)
      +delty*std::sin(myCoords.ori))>0)
      &&(b->identite!=(*it)->identite)){//Si les deux bestioles sont proches, qu'elles s'approchent et qu'elles sont différentes
         myCoords.ori=-myCoords.ori;//on inverse les directions
         theirCoords.ori=-theirCoords.ori;//on inverse les directions
         double transition=myCoords.vite;//on échange les vitesses
         myCoords.vite=theirCoords.vite;//on échange les vitesses
         theirCoords.vite=transition;//on échange les vitesses
         b->setCoords(myCoords);//attribution des coordonnées
         (*it)->setCoords(theirCoords);//attribution des coordonnées

         if((static_cast<double>(std::rand())/RAND_MAX)/(b->getResist())>=DBestiole::SURVIVE_COLLISION){
            b->killMe();//si le tirage aléatoire est plus élevé que les chances de survies, alors on tue la bestiole
         }
         if((static_cast<double>(std::rand())/RAND_MAX)/((*it)->getResist())>=DBestiole::SURVIVE_COLLISION){
            (*it)->killMe();//si le tirage aléatoire est plus élevé que les chances de survies, alors on tue la bestiole
         }
      }
   }
}
int Milieu::Count() const{//Nombre de bestioles dans le milieu
   return listeBestioles.size();//on renvoie la taille de la liste
}
void Milieu::describeMe() const{//On décrit le milieu
   cout<<"Milieu :"<<endl;
   for(auto b=listeBestioles.begin();b!=listeBestioles.end();++b){
      cout<<(*b)->getType()<<endl;//on renvoie le type de toutes les bestioles
   }
}
std::map<std::string,int> Milieu::contenu() const{//On compte les effectifs de chaque type
   std::map<std::string,int> ans;//initialisation
   for(auto lf=listeFactories.begin();lf!=listeFactories.end();++lf){
      ans.emplace(make_pair(lf->getTypeName(),0));//On construit les listes avec tous les types initiaux déclarés par les factories initiales
   }
   ans.emplace(make_pair(Interpreter::Others,0));//On rajoute une catégorie "autres types"
   for(auto b=listeBestioles.begin();b!=listeBestioles.end();++b){
      auto k = ans.find((*b)->getType());//pour chaque bestiole on récupère son type
      if(k==ans.end()){
         k=ans.find(Interpreter::Others);//ou le type autre sinon
      }
      k->second+=1;//et on incrémente le compteur correspondant
   }
   return ans;//on renvoie la map des noms et des effectifs
}
