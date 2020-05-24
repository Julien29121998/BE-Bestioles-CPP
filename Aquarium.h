#ifndef _AQUARIUM_H_
#define _AQUARIUM_H_


#include <iostream>
#include <CImg.h>

using namespace std;
using namespace cimg_library;


class Milieu;
struct Interpreter;

/** L'Aquarium contenant le milieu de simulation*/
class Aquarium : public CImgDisplay
{

private :
   Milieu        *flotte;
   int            delay;
   bool           paused;
   Interpreter   *myReader;

public :
   /**Constructeur d'Aquarium*/
   Aquarium( int pop,int width, int height, int _delay, Interpreter* interp);
   /**Destructeur d'Aquarium*/
   ~Aquarium( void );

   /**getter du milieu*/
   Milieu & getMilieu( void ) { return *flotte; }

   /*Lancer la simulation*/
   void run( void );

};


#endif
