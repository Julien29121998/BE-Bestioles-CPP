#include "DBestiole.h"
#include <cstdlib>
#include <cmath>
#include "Milieu.h"

const double       DBestiole::AFF_SIZE = 8.;
const double       DBestiole::MAX_VITESSE = 6.5;
const double       DBestiole::MAX_PHI =1.;
const double       DBestiole::MIN_PHI =0.;
const double       DBestiole::MAX_DELTA_O = 39.6;
const double       DBestiole::MIN_DELTA_O =11.5;   
const double       DBestiole::MAX_GAMMA_O=1.;
const double       DBestiole::MIN_GAMMA_O=0.;
const double       DBestiole::MAX_DELTA_Y =68.8;
const double       DBestiole::MIN_DELTA_Y =16.5;   
const double       DBestiole::MAX_GAMMA_Y=1.;
const double       DBestiole::MIN_GAMMA_Y=0.;
const double       DBestiole::MAX_ALPHA=4.59;
const double       DBestiole::MIN_ALPHA=0.31;
const double       DBestiole::MAX_OMEGA =4.5;
const double       DBestiole::MAX_ETA =2.9;
const double       DBestiole::MAX_NU =2.7;
const double       DBestiole::CLONE_RATE = 0.0008;
const double       DBestiole::GENERATION_RATE = 3.26;
const double       DBestiole::SURVIVE_COLLISION=0.88;
const double       DBestiole::PROPORTION_CHANGE=0.197;
const int          DBestiole::LIFE = 660;
long int           DBestiole::next = 0;

BParams::~BParams(){}
void BParams::PushWith(string key, Param_Dict& pd){
    pd.emplace(make_pair(key,this));
}

DBestiole::DBestiole()
{

   identite = ++next;
   cout << "const DBestiole (" << identite << ") par defaut : ";
   
}

DBestiole::~DBestiole()
{

   cout << "dest DBestiole" << identite << endl;

}

char* DBestiole::showID() const{
   static char id[64];
   sprintf(id, "%ld", identite);
   return id;
}

