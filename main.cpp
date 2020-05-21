#include "Aquarium.h"
#include "Milieu.h"
#include "Factory.h"
#include "DBestiole.h"
#include "Bestiole.h"
#include "Membre.h"
#include "Camouflages.h"
#include "Nageoire.h"
#include "Carapace.h"
#include "Capteur.h"
#include "Oreilles.h"
#include "Interpreter.h"

#include <iostream>
#include <fstream>

using namespace std;


int main()
{

   Aquarium       ecosysteme( 60, 800, 600, 30 );

   Interpreter i;

   i.fromFile("InputData.txt",ecosysteme);
   ecosysteme.run();


   return 0;

}
