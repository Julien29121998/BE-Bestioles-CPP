#include "Aquarium.h"
#include "Milieu.h"
#include "Bestiole.h"
#include "Membre.h"
#include "Camouflages.h"

#include <iostream>

using namespace std;


int main()
{

   Aquarium       ecosysteme( 640, 480, 30 );

   for ( int i = 1; i <= 20; ++i ){
      DBestiole* bo = new Camouflages(new Bestiole());
      bo->setExterne(bo);
      ecosysteme.getMilieu().addMember(bo);
   }
   ecosysteme.run();


   return 0;

}
