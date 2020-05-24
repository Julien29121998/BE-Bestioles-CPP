#ifndef _MILIEU_H_
#define _MILIEU_H_


#include "UImg.h"
#include "DBestiole.h"
#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Factory;
class IComportement;

/**Milieu de vie des Bestioles*/
class Milieu : public UImg
{

private :
   static const T            white[];//blanc

   int                       width, height;//taille du milieu
   int                       target_pop;//population visée
   int                       timer;//temps

   std::vector<DBestiole*>   listeBestioles;//liste des bestioles présentes

public :
   std::vector<IComportement*> Comportements_Disponibles;//comportements disponibles pour les bestioles
   IComportement*              Comportement_par_defaut;//Comportement par défaut
   std::vector<Factory>        listeFactories;//liste des factories de bestioles

   /**Constructeur du Milieu*/
   Milieu( int _width, int _height, int target_population );
   /**Destructeur du milieu*/
   ~Milieu();

   /**Retourner la largeur*/
   int getWidth() const { return width; };
   /**Retourner la hauteur*/
   int getHeight() const { return height; };

   /**Avancer la simulation d'une époque*/
   void step(std::vector<Factory> nf);

   /**Compter les bestioles visibles par une bestiole donnée, dans le milieu*/
   int nbVoisins( const DBestiole* b );
   /**Lister les bestioles visibles par une bestiole donnée, dans le milieu*/
   std::vector<DBestiole*> QuiVoisJe( const DBestiole* b);
   /**Tuer une bestiole d'id donné*/
   void kill(int id);
   /**Introduire les bestioles selon les factories*/
   void introduire();
   /**Gérer les collisions d'une bestiole avec les autres*/
   void handleCollisions(DBestiole* b);
   /**Décrire le milieu*/
   void describeMe() const;
   /**Compter les bestioles du milieu*/
   int Count() const;
   /**Indiquer les comptes des différents types de bestioles dans le milieu*/
   std::map<std::string,int> contenu() const;
};


#endif
