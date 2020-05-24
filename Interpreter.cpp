#include <iostream>
#include <fstream>
#include "Interpreter.h"

using namespace std;
//définition des constantes pour l'écriture
const string Interpreter::OutputFile="Output.csv";
const string Interpreter::Others="Autres";

Interpreter::Interpreter(){//Constructeur
   cpm = new CamoParams;kpm = new CaraParams;npm = new NageoParams;
   opm = new OreParams;ypm = new YeuxParams;compm = new ComportParams;//On initialise tous les paramètres
   sum=0.0;ecosysteme=nullptr;//On met la somme des proportions à 0, l'ecosysteme sur null
}
Interpreter::~Interpreter(){
   delete cpm;delete kpm;delete npm;delete opm;delete ypm;delete compm;//On supprime tout
   if(ecosysteme!=nullptr) delete ecosysteme;//On supprime l'ecosysteme si il a été créé
}
string Interpreter::readWord(string& line){//On lit un mot
    string word;
    int found = line.find(" ");//On récupère l'indice du premier espace
    word=line.substr(0,found);//on coupe la string en deux : le mot qu'on récupère
    line=line.substr(found+1,line.size());//et l'autre moitié qu'on met à jour
    return word;//on retourne le mot
}
double Interpreter::readBType(istream& source, string first_line, vector<Factory>& dest){//On lit un type de bestiole
    double proportion=1.0; //proportion par défaut
    string line;//strings de lecture: ligne
    string word;//strings de lecture: mot
    string type;//strings de lecture: type de bestiole
    line=first_line;//première ligne déja lue par une autre fonction avant celle-ci
    word=this->readWord(line);//on lit un mot
    if(word!="p:"){//si c'est un mot de type
        type=word;//on récupère cela comme un type
        word=this->readWord(line);//on passe au mot suivant
    }
    else{//Sinon on en génère un aléatoire
        char _type[16];
        sprintf(_type,"t%d",rand()%1000000);
        type=string(_type);
    }
    cout<<"Lecture du type "<<type<<":"<<endl;
    this->paramsf.erase(paramsf.begin(),paramsf.end());//on vide les paramètres
    if(word!="p:"){//si il n'y a pas de proportion ce sera 1
        cout<<"ATTENTION: Pas de proportion... par défaut 1, risque de produire des résultats non demandés !"<<endl;
        line=word+line;//On remet le mot lu puisqu'il ne nous concerne pas
    }
    else{//si il y a une proportion
        word=this->readWord(line);//on lit le mot suivant
        try{
        proportion=stod(word);//il est la valeur de la proportion
        }
        catch(invalid_argument){
            cout<<"ATTENTION: \""<<word<<"\" n'est pas une proportion. Par défaut 1."<<endl;
            line=word+line;//si ce n'est pas un chiffre on le remet
        }
    }
    string previous;
    while(previous=word,previous!=(word=this->readWord(line))){
        cout<<"ATTENTION: Contenu non lu: "<<word<<"... Sur la ligne, rien ne doit suivre la déclaration de type de bestiole"<<endl;
    }//on dit que tout ce qui suit n'est pas lisible
    while(getline(source,line),line.empty()){cout<<"...";}//On passe les lignes vides
    this->readCaracs(source,line, dest,proportion,type);//on lit les caractéristiques
    return proportion;//on renvoie la proportion lue
}
void Interpreter::readCaracs(istream& source, string first_line, vector<Factory>& dest, double proportion, string type){//On lit les caractéristiques d'une bestiole
    bool hasComp=false;//on n'a pas encore lu de comportement
    string line;//strings de lecture: ligne
    string word;//strings de lecture: mot
    line=first_line;//première ligne déja lue par une autre fonction avant celle-ci
    word=this->readWord(line);//on lit le mot suivant, définissant une caractéristique
    for(;;){//on exploite ce mot pour ajouter les paramètres de caractéristiques correspondants
        if(word=="Camouflages") this->readCamoParam(line,word);
        else if(word=="Carapace") this->readCaraParam(line,word);
        else if(word=="Nageoire") this->readNageoParam(line,word);
        else if(word=="Oreilles") this->readOreParam(line,word);
        else if(word=="Yeux") this->readYeuxParam(line,word);
        else if(word=="Comportement") hasComp=this->readComportParam(line,word);//si c'est un comportement, on dit que le comportement a été choisi
        else if(!word.empty()){break;};//si c'est incompréhensible on abandonne
        getline(source,line),word=this->readWord(line);//on lit la ligne suivante et son premier mot
    }
    if(!hasComp){//Si il n'y a pas de comportement on avertit que la bestiole sera Dumb
        cout<<"ATTENTION: Pas de Comportement Déclaré pour ce type de Bestiole: ce type de Bestioles aura le comportement par défaut"<<endl;
    }
    Factory fact = Factory(paramsf,proportion,type);//On crée la factory correspondant aux paramètres
    dest.push_back(fact);//On l'ajoute à la liste de factories
    while(!(word=="Stop"||word=="STOP")){//Tant qu'il n'y a aucun stop, on lit
        if(word=="Bestioles")continue;//Si on redéclare un bloc de bestioles, on néglige la ligne
        else if(word=="Type"){sum+=this->readBType(source,line,dest);break;}//Si c'est un nouveau type, on le lit, et on arrête d'attendre
        else if(word.empty())cout<<"...";//si c'est une ligne vide, on la passe
        else{
            cout<<"ATTENTION: erreur de lecture: "<<word<<endl;//si un mot est illisible
            break;
        }
        getline(source,line),word=this->readWord(line);//on passe à la ligne suivante

    }
}
void Interpreter::readCamoParam(string& line,string& word){//lire une caractéristique camouflage
    bool correctphi=false;//elle n'a pas encore eu ses paramètres définis
    string previous;
    while(previous=word,previous!=(word=this->readWord(line))){//tant que la ligne est lisible, on cherche à lire ces paramètres
        if(word=="phi"){try{cpm->phi=stod((word=readWord(line),word));correctphi=true;}catch(invalid_argument){cout<<word<<endl;};}
    }
    if(correctphi){//Si tous les paramètres sont corrects, on peut ajouter la carctéristique
        cpm->Add(paramsf);
        cout<<"Camouflages "<<cpm->phi<<endl;
    }
    else{
        cout<<"ATTENTION: Camouflages invalides"<<endl;//Sinon elle est invalide
    }
}
void Interpreter::readCaraParam(string& line,string& word){//lire une caractéristique carapace
    bool correctomega=false,correcteta=false;//elle n'a pas encore eu ses paramètres définis
    string previous;
    while(previous=word,previous!=(word=this->readWord(line))){//tant que la ligne est lisible, on cherche à lire ces paramètres
        if(word=="omega"){try{kpm->omega=stod((word=readWord(line),word));correctomega=true;}catch(invalid_argument){cout<<word<<endl;};}
        if(word=="eta"){try{kpm->eta=stod((word=readWord(line),word));correcteta=true;}catch(invalid_argument){cout<<word<<endl;};}        
    }
    if(correctomega&&correcteta){//Si tous les paramètres sont corrects, on peut ajouter la carctéristique
        kpm->Add(paramsf);
        cout<<"Carapace "<<kpm->omega<<"; "<<kpm->eta<<endl;//Sinon elle est invalide
    }
    else{
        cout<<"ATTENTION: Carapace invalide"<<endl;
    }
}
void Interpreter::readNageoParam(string& line,string& word){//lire une caractéristique nageoire
    bool correctnu=false;//elle n'a pas encore eu ses paramètres définis
    string previous;
    while(previous=word,previous!=(word=this->readWord(line))){//tant que la ligne est lisible, on cherche à lire ces paramètres
        if(word=="nu"){try{npm->nu=stod((word=readWord(line),word));correctnu=true;}catch(invalid_argument){cout<<word<<endl;};}
    }
    if(correctnu){//Si tous les paramètres sont corrects, on peut ajouter la carctéristique
        npm->Add(paramsf);
        cout<<"Nageoire "<<npm->nu<<endl;//Sinon elle est invalide
    }
    else{
        cout<<"ATTENTION: Nageoires invalides"<<endl;
    }
}
void Interpreter::readOreParam(string& line,string& word){//lire une caractéristique oreilles
    bool correctdelta=false,correctgamma=false;//elle n'a pas encore eu ses paramètres définis
    string previous;
    while(previous=word,previous!=(word=this->readWord(line))){//tant que la ligne est lisible, on cherche à lire ces paramètres
        if(word=="delta"){try{opm->delta=stod((word=readWord(line),word));correctdelta=true;}catch(invalid_argument){cout<<word<<endl;};}
        if(word=="gamma"){try{opm->gamma=stod((word=readWord(line),word));correctgamma=true;}catch(invalid_argument){cout<<word<<endl;};}
    }
    if(correctdelta&&correctgamma){//Si tous les paramètres sont corrects, on peut ajouter la carctéristique
        opm->Add(paramsf);
        cout<<"Oreilles "<<opm->delta<<"; "<<opm->gamma<<endl;//Sinon elle est invalide
    }
    else{
        cout<<"ATTENTION: Oreilles invalides"<<endl;
    }
}
void Interpreter::readYeuxParam(string& line,string& word){//lire une caractéristique yeux
    bool correctdelta=false,correctgamma=false,correctalpha=false;
    string previous;
    while(previous=word,previous!=(word=this->readWord(line))){//tant que la ligne est lisible, on cherche à lire ces paramètres
        if(word=="delta"){try{ypm->delta=stod((word=readWord(line),word));correctdelta=true;}catch(invalid_argument){cout<<word<<endl;};}
        if(word=="gamma"){try{ypm->gamma=stod((word=readWord(line),word));correctgamma=true;}catch(invalid_argument){cout<<word<<endl;};}
        if(word=="alpha"){try{ypm->alpha=stod((word=readWord(line),word));correctalpha=true;}catch(invalid_argument){cout<<word<<endl;};}
    }
    if(correctdelta&&correctgamma&&correctalpha){//Si tous les paramètres sont corrects, on peut ajouter la carctéristique
        ypm->Add(paramsf);
        cout<<"Yeux "<<ypm->delta<<"; "<<ypm->gamma<<"; "<<ypm->alpha<<endl;//Sinon elle est invalide
    }
    else{
        cout<<"ATTENTION: Yeux invalides"<<endl;
    }
}
bool Interpreter::readComportParam(string& line,string& word){//lire une caractéristique comportement
    word=this->readWord(line);//On lit le mot correspondant au comportement et on le définit correctement
    if(word=="Multiple")compm->Comportement=COMP_MULTIPLE;
    else if(word=="Peureuse")compm->Comportement=COMP_PEUREUSE;
    else if(word=="Kamikaze")compm->Comportement=COMP_KAMIKAZE;
    else if(word=="Prevoyante"||word=="Prévoyante")compm->Comportement=COMP_PREVOYANTE;
    else if(word=="Gregaire"||word=="Grégaire")compm->Comportement=COMP_GREGAIRE;
    else {cout<<"Comportement inconnu :"<<word<<endl;return false;}//Si le comportement est inconnu ou illisible c'est une erreur
    compm->Add(paramsf);//si il est correct on l'ajoute et c'est une réussite
    cout<<"Comportement: "<<compm->Comportement<<endl;
    return true;
}
void Interpreter::fromFile(string file){//lire un fichier et créer une simulation
    string line;//string de lecture:ligne
    string word;//string de lecture:mot
    ifstream input;//flux d'entrée
    bool isDefined=false;//si la simulation est définie ou pas: pas encore
    input.open(file);//on lit la source
    getline(input,line),word=this->readWord(line);//premier mot
    while(!(word=="Stop"||word=="STOP")){//tant qu'il ne s'agit pas d'un stop
        if(word=="Bestioles"&&isDefined){//Si le mot déclare un bloc de bestioles et que la simulation a été définie, on peut commencer à lire des types
            while(getline(input,line),word=this->readWord(line),line.empty()){cout<<"...";}//lignes vides
            if(word=="Type"){//On lit un type
                sum+=readBType(input,line, ecosysteme->getMilieu().listeFactories);break;//on compte la proportion en plus dans la somme des proportions
            }
        }
        else if(word=="Simulation"&&!isDefined){//si le mot déclare un bloc simulation et que celle ci n'a pas été encore définie, on la définit
            while(getline(input,line),word=this->readWord(line),word=="Propriété"||word=="Propriete"||word.empty()){//tant qu'on peut lire des propriétés
                if(word.empty()){//lignes vides
                    cout<<"...";
                }else{
                    readProp(line);//on lit des propriétés
                }
            }
            isDefined=true;//la simulation est dite définie
            ecosysteme=new Aquarium(Population,Width,Height, 30, this);//on crée l'écosystème
            continue;//on reprend la lecture
        }
        else if(word.empty()){cout<<"...";}//lignes vides
        else{
            cout<<"ATTENTION: erreur de lecture: "<<word<<endl;//erreurs de lecture: mots illisibles
            break;
        }
        getline(input,line),word=this->readWord(line);//ligne suivantes, mot de la ligne

    }
    if(sum!=1.){//warning si jamais la somme des proportions n'est pas 1
        cout<<"ATTENTION: la Somme des Proportions n'est pas 1 ("<<sum<<"). Effectifs réels des Bestiole Indéfini (Sera supérieur ou inférieur à la valeur donnée)..."<<endl;
    }
    input.close();//on arrête de lire
    if(ecosysteme!=nullptr){//si l'ecosysteme est lu on démarre la simulation
        cout<<"DEBUT DE LA SIMULATION"<<endl;
        ecosysteme->run();
    }
}
void Interpreter::readProp(string& line){//Lire une propriété de la simulation
    string word="Propriété Introuvable";//par défaut le mot lu est "introuvable"
    string paramName;//nom du paramètre
    double readv;//valeur lue
    bool valid=false;//lecture invalide au début
    float defaultvalue=0.;//valeur par défaut pour afficher en cas de mauvais input
    paramName=this->readWord(line);//on lit la propriété et sa valeur ensuite, dont on vérifie la validité ensuite
    if(paramName=="AFF_SIZE"){word=this->readWord(line);try{readv=stod(word);valid=(readv>=3.1);}catch(invalid_argument){}DBestiole::AFF_SIZE=(valid?readv:defaultvalue=DBestiole::AFF_SIZE);}
    else if(paramName=="MULTIPLE_CHANGE_RATE"){word=this->readWord(line);try{readv=stoi(word);valid=(readv>=10);}catch(invalid_argument){}IComportement::MULTIPLE_CHANGE_RATE=(valid?readv:defaultvalue=IComportement::MULTIPLE_CHANGE_RATE);}
    else if(paramName=="MAX_VITESSE"){word=this->readWord(line);try{readv=stod(word);valid=(readv>=2.&&readv<=10.);}catch(invalid_argument){}DBestiole::MAX_VITESSE=(valid?readv:defaultvalue=DBestiole::MAX_VITESSE);}
    else if(paramName=="MAX_PHI"){word=this->readWord(line);try{readv=stod(word);valid=(readv>=DBestiole::MIN_PHI&&readv>=0);}catch(invalid_argument){}DBestiole::MAX_PHI=(valid?readv:defaultvalue=DBestiole::MAX_PHI);}
    else if(paramName=="MIN_PHI"){word=this->readWord(line);try{readv=stod(word);valid=(readv<=DBestiole::MAX_PHI&&readv>=0);}catch(invalid_argument){}DBestiole::MIN_PHI=(valid?readv:defaultvalue=DBestiole::MIN_PHI);}
    else if(paramName=="MAX_DELTA_O"){word=this->readWord(line);try{readv=stod(word);valid=(readv>=DBestiole::MIN_DELTA_O&&readv>=0);}catch(invalid_argument){}DBestiole::MAX_DELTA_O=(valid?readv:defaultvalue=DBestiole::MAX_DELTA_O);}
    else if(paramName=="MIN_DELTA_O"){word=this->readWord(line);try{readv=stod(word);valid=(readv<=DBestiole::MAX_DELTA_O&&readv>=0);}catch(invalid_argument){}DBestiole::MIN_DELTA_O=(valid?readv:defaultvalue=DBestiole::MIN_DELTA_O);}
    else if(paramName=="MAX_GAMMA_O"){word=this->readWord(line);try{readv=stod(word);valid=(readv>=DBestiole::MIN_GAMMA_O&&readv>=0);}catch(invalid_argument){}DBestiole::MAX_GAMMA_O=(valid?readv:defaultvalue=DBestiole::MAX_GAMMA_O);}
    else if(paramName=="MIN_GAMMA_O"){word=this->readWord(line);try{readv=stod(word);valid=(readv<=DBestiole::MAX_GAMMA_O&&readv>=0);}catch(invalid_argument){}DBestiole::MIN_GAMMA_O=(valid?readv:defaultvalue=DBestiole::MIN_GAMMA_O);}
    else if(paramName=="MAX_DELTA_Y"){word=this->readWord(line);try{readv=stod(word);valid=(readv>=DBestiole::MIN_DELTA_Y&&readv>=0);}catch(invalid_argument){}DBestiole::MAX_DELTA_Y=(valid?readv:defaultvalue=DBestiole::MAX_DELTA_Y);}
    else if(paramName=="MIN_DELTA_Y"){word=this->readWord(line);try{readv=stod(word);valid=(readv<=DBestiole::MAX_DELTA_Y&&readv>=0);}catch(invalid_argument){}DBestiole::MIN_DELTA_Y=(valid?readv:defaultvalue=DBestiole::MIN_DELTA_Y);}
    else if(paramName=="MAX_GAMMA_Y"){word=this->readWord(line);try{readv=stod(word);valid=(readv>=DBestiole::MIN_GAMMA_Y&&readv>=0);}catch(invalid_argument){}DBestiole::MAX_GAMMA_Y=(valid?readv:defaultvalue=DBestiole::MAX_GAMMA_Y);}
    else if(paramName=="MIN_GAMMA_Y"){word=this->readWord(line);try{readv=stod(word);valid=(readv<=DBestiole::MAX_GAMMA_Y&&readv>=0);}catch(invalid_argument){}DBestiole::MIN_GAMMA_Y=(valid?readv:defaultvalue=DBestiole::MIN_GAMMA_Y);}
    else if(paramName=="MAX_ALPHA"){word=this->readWord(line);try{readv=stod(word);valid=(readv>=DBestiole::MIN_ALPHA&&readv>=0&&readv<=2*M_PI);}catch(invalid_argument){}DBestiole::MAX_ALPHA=(valid?readv:defaultvalue=DBestiole::MAX_ALPHA);}
    else if(paramName=="MIN_ALPHA"){word=this->readWord(line);try{readv=stod(word);valid=(readv<=DBestiole::MAX_ALPHA&&readv>=0&&readv<=2*M_PI);}catch(invalid_argument){}DBestiole::MIN_ALPHA=(valid?readv:defaultvalue=DBestiole::MIN_ALPHA);}
    else if(paramName=="MAX_OMEGA"){word=this->readWord(line);try{readv=stod(word);valid=(readv<=10.0&&readv>=1.0);}catch(invalid_argument){}DBestiole::MAX_OMEGA=(valid?readv:defaultvalue=DBestiole::MAX_OMEGA);}
    else if(paramName=="MAX_ETA"){word=this->readWord(line);try{readv=stod(word);valid=(readv<=5.5&&readv>=1.0);}catch(invalid_argument){}DBestiole::MAX_ETA=(valid?readv:defaultvalue=DBestiole::MAX_ETA);}
    else if(paramName=="MAX_NU"){word=this->readWord(line);try{readv=stod(word);valid=(readv<=5.5&&readv>=1.0);}catch(invalid_argument){}DBestiole::MAX_NU=(valid?readv:defaultvalue=DBestiole::MAX_NU);}
    else if(paramName=="CLONE_RATE"){word=this->readWord(line);try{readv=stod(word);valid=(readv<=0.1&&readv>=0);}catch(invalid_argument){}DBestiole::CLONE_RATE=(valid?readv:defaultvalue=DBestiole::CLONE_RATE);}
    else if(paramName=="GENERATION_RATE"){word=this->readWord(line);try{readv=stod(word);valid=(readv<=10.0&&readv>=0);}catch(invalid_argument){}DBestiole::GENERATION_RATE=(valid?readv:defaultvalue=DBestiole::GENERATION_RATE);}
    else if(paramName=="SURVIVE_COLLISION"){word=this->readWord(line);try{readv=stod(word);valid=(readv<=1.0&&readv>=0);}catch(invalid_argument){}DBestiole::SURVIVE_COLLISION=(valid?readv:defaultvalue=DBestiole::SURVIVE_COLLISION);}
    else if(paramName=="PROPORTION_CHANGE"){word=this->readWord(line);try{readv=stod(word);valid=(readv<=1.0&&readv>=0);}catch(invalid_argument){}DBestiole::PROPORTION_CHANGE=(valid?readv:defaultvalue=DBestiole::PROPORTION_CHANGE);}
    else if(paramName=="LIFE"){word=this->readWord(line);try{readv=stoi(word);valid=(readv<=2000&&readv>=20);}catch(invalid_argument){}DBestiole::LIFE=(valid?readv:defaultvalue=DBestiole::LIFE);}
    else if(paramName=="POPULATION"){word=this->readWord(line);try{readv=stoi(word);valid=(readv<=300&&readv>=0);}catch(invalid_argument){}Population=(valid?readv:defaultvalue=Population);}
    else if(paramName=="WINDOW_W"){word=this->readWord(line);try{readv=stoi(word);valid=(readv>=400);}catch(invalid_argument){}Width=(valid?readv:defaultvalue=Width);}
    else if(paramName=="WINDOW_H"){word=this->readWord(line);try{readv=stoi(word);valid=(readv>=400);}catch(invalid_argument){}Height=(valid?readv:defaultvalue=Height);}
    else{cout<<"ATTENTION: Propriété "<<paramName<<" inconnue..."<<endl;}//si le nom est inconnu
    if(!valid){cout<<"ATTENTION: Valeur illisible ou inappropriée pour la propriété "<<paramName<<": "<<word<<"... valeur remplacée par la valeur prédéfinie "<<defaultvalue<<endl;}//si la valeur est inadaptée

}