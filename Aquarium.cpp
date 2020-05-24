#include "Aquarium.h"

#include "Milieu.h"
#include "Interpreter.h"
#include <fstream>


Aquarium::Aquarium( int target_population,int width, int height, int _delay, Interpreter* interp ) : CImgDisplay(), delay( _delay )
{//Constructeur

   int         screenWidth = 1280; //screen_width;
   int         screenHeight = 1024; //screen_height;
   paused = false;//pas en pause


   //cout << "const Aquarium" << endl;
   myReader = interp;//on garde l'interpreteur pour lire certaines commandes
   flotte = new Milieu( width, height, target_population );//Milieu
   assign( *flotte, "Simulation d'ecosysteme" );//fenêtre

   move( static_cast<int>((screenWidth-width)/2), static_cast<int>((screenHeight-height)/2) );//position

}


Aquarium::~Aquarium( void )//destructeur d'aquarium
{

   delete flotte;//on détruit le milieu

   //cout << "dest Aquarium" << endl;

}


void Aquarium::run( void )//Fonctionnement de la simulation
{
   std::vector<Factory> temp;//effets de commandes potentielles: factories temporaires

   cout << "running Aquarium" << endl;
   this->flotte->introduire();//remplissage initial du milieu par les factories
   std::ofstream file;//fichier de sortie
   file.open (Interpreter::OutputFile);//ouverture
   file<<"timer,"<<Interpreter::Others<<",";//headers de base
   std::vector<Factory> contenu = this->flotte->listeFactories;//factories
   for(auto cc=contenu.begin();cc!=contenu.end();++cc){
      file<<cc->getTypeName()<<",";//headers des types des factories
   }
   file<<endl;
   file.close();//complétion

   while ( ! is_closed() )//boucle de la simulation
   {
      if ( is_key() ) {//touche pressée
         cout << "Vous avez presse la touche " << static_cast<unsigned char>( key() );
         cout << " (" << key() << ")" << endl;
         if ( is_keyESC() ){close();}//esc=fermer
         if ( is_keySPACE() ){paused=!paused;wait(10*delay);cout<<"PAUSE"<<endl;}//pause -> wait pour éviter un déclenchement en continu lors de l'appui
         if ( is_keyK()){//commande tuer
            cout<<"Vous avez saisi K: Veuillez entrer un numéro de bestiole à tuer:"<<endl;
            string line;
            getline(cin, line);//lire dans la console
            try{
            int killval = stoi(line);//l'id à tuer
            cout <<"kill "<< killval <<endl;
            flotte->kill(killval);//tuer la bonne créature
            cout <<"Simulation en Pause. Appuyez sur SPACEBAR dans la simulation pour reprendre "<<endl;
            paused=true;//pause
            }
            catch(std::invalid_argument e)
            {
               cout<<"è_é"<<endl;
            }
         }
         if( is_keyN()){//faire naitre une créature
            cout<<"Vous avez saisi N: Entrez des instructions de création d'une bestiole, avec une proportion égale au nombre voulu, puis écrivez STOP"<<endl;
            string line;
            getline(cin, line);//première ligne de commande
            if(myReader->readWord(line)=="Type"){
            myReader->readBType(cin,line,temp);//on utilise l'interpreter pour le reste si cela est valide. On remplit la liste temporaire de factories.
            }
         cout <<"Simulation en Pause. Appuyez sur SPACEBAR dans la simulation pour reprendre "<<endl;
         paused=true;//pause
         }
         if( is_keyC()){//compter
            cout<<"Nombre de Créatures :"<<flotte->Count()<<endl;wait(10*delay);//on utilise count
         }
         if( is_keyR()){//résumer
            flotte->describeMe();wait(10*delay);//on utilise describe
         }
      }
      if(!paused){//si la simulation est en cours, en déclenche une étape.
         flotte->step(temp);//époque du milieu
         temp.erase(temp.begin(),temp.end());//effacer les factories temporaires après usage
      }
      display( *flotte );//affichage
      wait( delay );//pause entre les époques
      
   }

}
