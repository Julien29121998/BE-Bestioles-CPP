#ifndef _DBESTIOLE_H_
#define _DBESTIOLE_H_


#include "UImg.h"

#include <iostream>
#include <map>

class Milieu;
class Interpreter;
struct BParams;

using namespace std;
using Param_Dict = std::map<std::string,BParams*>;

/**Une paire de paire de coordonnées, et de paire de coordonnées de vitesse*/ 
typedef struct paire {
   int x;
   int y;
   double ori;
   double vite;

} paire_t;

/**Paramètres de création*/
struct BParams
{
/**Constructeur*/
BParams();
/**Destructeur*/
virtual ~BParams();
/**Ajouter à un dictionnaire de paramètres avec une clé string*/
void PushWith(string key,Param_Dict& pd);
/**Ajouter à un dictionnaire de paramètres*/
virtual void Add(Param_Dict& pd)=0;
/*Copier ces paramètres*/
virtual BParams* cppm() const=0;
};
/**Abstraction de Bestiole ou de décorateur de Bestiole*/
class DBestiole{
friend class Milieu;
friend class Interpreter;
/**Paramètres de Simulation*/
protected :
   static double     AFF_SIZE;
   static double     MAX_VITESSE;
   static double     MAX_PHI;
   static double     MIN_PHI;
   static double     MAX_DELTA_O;
   static double     MIN_DELTA_O;
   static double     MAX_GAMMA_O;
   static double     MIN_GAMMA_O;
   static double     MAX_DELTA_Y;
   static double     MIN_DELTA_Y;
   static double     MAX_GAMMA_Y;
   static double     MIN_GAMMA_Y;
   static double     MAX_ALPHA;
   static double     MIN_ALPHA;  
   static double     MAX_NU;
   static double     MAX_OMEGA;
   static double     MAX_ETA;
   static double     GENERATION_RATE;
   static double     CLONE_RATE;
   static double     SURVIVE_COLLISION;
   static double     PROPORTION_CHANGE;
   static int        LIFE;

private :
   /*ID suivant à créer*/
   static long int              next;
   /*ID Bestiole*/
   long int                     identite;
 
public : 
   /**Constructeur*/                                     
   DBestiole(); 
   /**Destructeur*/                              
   virtual ~DBestiole(); 
   /**Renvoie la vitesse Max*/
   static double getVmax(){return MAX_VITESSE;};  
   /**Renvoie l'id de cette partie de bestiole*/                 
   char* showID() const;
   /**La bestiole agit selon son comportement pour déterminer sa vitesse et son orientation*/
   virtual void action( Milieu & monMilieu)=0;
   /**Affichage de la bestiole*/
   virtual void draw( UImg & support )=0;
   /**La bestiole se déplace*/
   virtual void bouge(Milieu& monMilieu, double coef, paire_t objectif)=0;
   /**Perception d'une autre bestiole avec celle-ci*/
   virtual bool jeTeVois( const DBestiole* b ) const=0;
   /**Initialiser aléatoirement les coordonnées de la bestiole*/
   virtual void initCoords( int xLim, int yLim )=0;
   /**Obtenir la visibilité de la bestiole*/
   virtual double getVisibilite() const=0;
   /**Obtenir la resistance de la bestiole*/
   virtual double getResist() const=0;
   /**Essayer de cloner la bestiole*/
   virtual DBestiole* randomCloning() const=0;
   /**faire vieillir la bestiole*/
   virtual bool vieillir()=0;
   /**définir la couche externe de la bestiole*/
   virtual void setExterne(DBestiole* p)=0;
   /**copier la bestiole*/
   virtual DBestiole* copy()=0;
   /**Récupérer les coordonnées de la Bestiole*/
   virtual paire_t getCoords() const=0;
   /**Tuer cette bestiole*/
   virtual void killMe()=0;
   /**Définir les coordonnées de la Bestiole*/
   virtual void setCoords(paire_t coords)=0;
   /**Récupérer le type de la bestiole*/
   virtual string getType() const=0;
   /**Redéfinir le type de la bestiole*/
   virtual void setType(string type)=0;

};


#endif
