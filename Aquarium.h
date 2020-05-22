#ifndef _AQUARIUM_H_
#define _AQUARIUM_H_


#include <iostream>
#include <CImg.h>

using namespace std;
using namespace cimg_library;


class Milieu;
struct Interpreter;


class Aquarium : public CImgDisplay
{

private :
   Milieu        *flotte;
   int            delay;
   bool           paused;
   Interpreter   *myReader;

public :
   Aquarium( int pop,int width, int height, int _delay, Interpreter* interp);
   ~Aquarium( void );

   Milieu & getMilieu( void ) { return *flotte; }

   void run( void );

};


#endif
