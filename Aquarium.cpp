#include "Aquarium.h"

#include "Milieu.h"
#include "Interpreter.h"
#include <fstream>


Aquarium::Aquarium( int target_population,int width, int height, int _delay, Interpreter* interp ) : CImgDisplay(), delay( _delay )
{

   int         screenWidth = 1280; //screen_width();
   int         screenHeight = 1024; //screen_height();
   paused = false;


   cout << "const Aquarium" << endl;
   myReader = interp;
   flotte = new Milieu( width, height, target_population );
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
   std::vector<Factory> temp;

   cout << "running Aquarium" << endl;
   this->flotte->introduire();
   std::ofstream file;
   file.open (Interpreter::OutputFile);
   file<<"timer,"<<Interpreter::Others<<",";
   std::vector<Factory> contenu = this->flotte->listeFactories;
   for(auto cc=contenu.begin();cc!=contenu.end();++cc){
      file<<cc->getTypeName()<<",";
   }
   file<<endl;
   file.close();

   while ( ! is_closed() )
   {
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
         if( is_keyN()){
            cout<<"Vous avez saisi N: Entrez des instructions de création d'une bestiole, avec une proportion égale au nombre voulu, puis écrivez STOP"<<endl;
            string line;
            getline(cin, line);
            if(myReader->readWord(line)=="Type"){
            myReader->readBType(cin,line,temp);
            }
         cout <<"Simulation en Pause. Appuyez sur SPACEBAR dans la simulation pour reprendre "<<endl;
         paused=true;
         }
         if( is_keyC()){
            cout<<"Nombre de Créatures :"<<flotte->Count()<<endl;wait(10*delay);
         }
         if( is_keyR()){
            flotte->describeMe();wait(10*delay);
         }
      }
      if(!paused){
         flotte->step(temp);
         temp.erase(temp.begin(),temp.end());
      }
      display( *flotte );
      wait( delay );
      
   }

}
