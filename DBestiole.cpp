#include "DBestiole.h"
#include <cstdlib>
#include <cmath>
#include "Milieu.h"
//Valeurs standard des paramètres de simulation
double       DBestiole::AFF_SIZE = 8.;
double       DBestiole::MAX_VITESSE = 6.5;
double       DBestiole::MAX_PHI =1.;
double       DBestiole::MIN_PHI =0.;
double       DBestiole::MAX_DELTA_O = 39.6;
double       DBestiole::MIN_DELTA_O =11.5;   
double       DBestiole::MAX_GAMMA_O=1.;
double       DBestiole::MIN_GAMMA_O=0.;
double       DBestiole::MAX_DELTA_Y =68.8;
double       DBestiole::MIN_DELTA_Y =16.5;   
double       DBestiole::MAX_GAMMA_Y=1.;
double       DBestiole::MIN_GAMMA_Y=0.;
double       DBestiole::MAX_ALPHA=4.59;
double       DBestiole::MIN_ALPHA=0.31;
double       DBestiole::MAX_OMEGA =4.5;
double       DBestiole::MAX_ETA =2.9;
double       DBestiole::MAX_NU =2.7;
double       DBestiole::CLONE_RATE = 0.0008;
double       DBestiole::GENERATION_RATE = 3.26;
double       DBestiole::SURVIVE_COLLISION=0.88;
double       DBestiole::PROPORTION_CHANGE=0.207;
int          DBestiole::LIFE = 660;
//On commence à compter à 0
long int           DBestiole::next = 0;

//construction et Destruction de Paramètres
BParams::BParams(){/*cout<<"p@"<<(this)<<endl;*/}
BParams::~BParams(){/*cout<<"~p@"<<(this)<<endl;*/}

void BParams::PushWith(string key, Param_Dict& pd){//Ajouter des paramètres à un dictionnaire avec une clé string
    pd.emplace(make_pair(key,this));//on ajoute au dictionnaire avec la clé voulue
}

DBestiole::DBestiole()//Constructeur
{

   identite = ++next;//On s'attribue l'identité, et la suivante s'incrémente aussi
   //cout << "const DBestiole (" << identite << ") par defaut : ";
   
}

DBestiole::~DBestiole()//Destructeur
{

  // cout << "dest DBestiole" << identite << endl;

}

char* DBestiole::showID() const{//On récupère l'ID de cette bestiole
   static char id[64];
   sprintf(id, "%ld", identite);//conversion en string
   return id;//retour
}

