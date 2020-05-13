#include "DBestiole.h"
#include <cstdlib>
#include <cmath>
#include "Milieu.h"

const double       DBestiole::AFF_SIZE = 8.;
const double       DBestiole::MAX_VITESSE = 10.;
const double       DBestiole::LIMITE_VUE = 30.;
const double       DBestiole::MAX_PHI =1.;
const double       DBestiole::MIN_PHI =0.;
const double       DBestiole::MAX_DELTA_O =15.4;
const double       DBestiole::MIN_DELTA_O =1.;   
const double       DBestiole::MAX_GAMMA_O=1.;
const double       DBestiole::MIN_GAMMA_O=0.;
const double       DBestiole::MAX_OMEGA =3.0;
const double       DBestiole::MAX_ETA =2.8;
const double       DBestiole::MAX_NU =6.5;
const int          DBestiole::LIFE = 250;
const int          DBestiole::CLONE_RATE = 440;
int                DBestiole::next = 0;


DBestiole::DBestiole()
{

   identite = ++next;
   cout << "const DBestiole (" << identite << ") par defaut" << endl;
   
}

DBestiole::~DBestiole()
{

   cout << "dest DBestiole" << identite << endl;

}

char* DBestiole::showID() const{
   static char id[64];
   sprintf(id, "%d", identite);
   return id;
}

