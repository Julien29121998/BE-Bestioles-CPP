#include "DBestiole.h"
#include <cstdlib>
#include <cmath>
#include "Milieu.h"

const double       DBestiole::AFF_SIZE = 8.;
const double       DBestiole::MAX_VITESSE = 10.;
const double       DBestiole::LIMITE_VUE = 30.;
const int          DBestiole::LIFE = 200;

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

