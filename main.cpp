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
   Interpreter i;//On crée un interpréteur
   i.fromFile("InputData.txt");//On exploite InputData.txt
   return 0;

}
