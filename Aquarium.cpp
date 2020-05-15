#include "Aquarium.h"

#include "Milieu.h"


Aquarium::Aquarium( int pop,int width, int height, int _delay ) : CImgDisplay(), delay( _delay )
{

   int         screenWidth = 1280; //screen_width();
   int         screenHeight = 1024; //screen_height();
   paused = false;


   cout << "const Aquarium" << endl;

   flotte = new Milieu( width, height );
   target_population = pop;
   assign( *flotte, "Simulation d'ecosysteme" );

   move( static_cast<int>((screenWidth-width)/2), static_cast<int>((screenHeight-height)/2) );

}


Aquarium::~Aquarium( void )
{

   delete flotte;

   cout << "dest Aquarium" << endl;

}


void Aquarium::run( void )
{

   cout << "running Aquarium" << endl;

   flotte->introduire(target_population);

   while ( ! is_closed() )
   {

      //iteration de la simulation

      if ( is_key() ) {
         cout << "Vous avez presse la touche " << static_cast<unsigned char>( key() );
         cout << " (" << key() << ")" << endl;
         if ( is_keyESC() ){close();}
         if ( is_keySPACE() ){paused=!paused;wait(10*delay);cout<<"PAUSE"<<endl;}
         if ( is_keyK()){
            cout<<"Vous avez saisi K: Veuillez entrer un numéro de bestiole à tuer:"<<endl;
            string line;
            getline(cin, line);
            try{
            int killval = stoi(line);
            cout <<"kill "<< killval <<endl;
            flotte->kill(killval);
            cout <<"Simulation en Pause. Appuyez sur SPACEBAR dans la simulation pour reprendre "<<endl;
            paused=true;
            }
            catch(std::invalid_argument e)
            {
               cout<<"è_é"<<endl;
            }
         }
      }
      if(!paused){
      flotte->step();
      }
      display( *flotte );
      wait( delay );
      
   } // while

}
