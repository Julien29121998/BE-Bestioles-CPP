#include <iostream>
#include <fstream>
#include "Interpreter.h"

using namespace std;

Interpreter::Interpreter(){
   cpm = new CamoParams;kpm = new CaraParams;npm = new NageoParams;
   opm = new OreParams;ypm = new YeuxParams;compm = new ComportParams;
   sum=0.0;ecosysteme=nullptr;
}
Interpreter::~Interpreter(){
   delete cpm;delete kpm;delete npm;delete opm;delete ypm;delete compm;
   if(ecosysteme!=nullptr) delete ecosysteme;
}
string Interpreter::readWord(string& line){
    string word;
    int found = line.find(" ");
    word=line.substr(0,found);
    line=line.substr(found+1,line.size());
    return word;
}
double Interpreter::readBType(istream& source, string first_line, vector<Factory>& dest){
    double proportion=1.0; 
    string line;
    string word;
    line=first_line;
    word=this->readWord(line);
    if(word!="p:"){
        cout<<"Lecture du type "<<word<<":"<<endl;
        word=this->readWord(line);
    }
    this->paramsf.erase(paramsf.begin(),paramsf.end());
    if(word!="p:"){
        cout<<"ATTENTION: Pas de proportion... par défaut 1, risque de produire des résultats non demandés !"<<endl;
        line=word+line;
    }
    else{
        word=this->readWord(line);
        try{
        proportion=stod(word);
        }
        catch(invalid_argument){
            cout<<"ATTENTION: \""<<word<<"\" n'est pas une proportion. Par défaut 1."<<endl;
            line=word+line;
        }
    }
    string previous;
    while(previous=word,previous!=(word=this->readWord(line))){
        cout<<"ATTENTION: Contenu non lu: "<<word<<"... Sur la ligne, rien ne doit suivre la déclaration de type de bestiole"<<endl;
    }
    while(getline(source,line),line.empty()){cout<<"...";}
    this->readCaracs(source,line, dest,proportion);
    return proportion;
}
void Interpreter::readCaracs(istream& source, string first_line, vector<Factory>& dest, double proportion){
    bool hasComp=false;
    string line;
    string word;
    line=first_line;
    word=this->readWord(line);
    for(;;){
        if(word=="Camouflages") this->readCamoParam(line,word);
        else if(word=="Carapace") this->readCaraParam(line,word);
        else if(word=="Nageoire") this->readNageoParam(line,word);
        else if(word=="Oreilles") this->readOreParam(line,word);
        else if(word=="Yeux") this->readYeuxParam(line,word);
        else if(word=="Comportement") hasComp=this->readComportParam(line,word);
        else if(!word.empty()){break;};
        getline(source,line),word=this->readWord(line);
    }
    if(!hasComp){
        cout<<"ATTENTION: Pas de Comportement Déclaré pour ce type de Bestiole: ce type de Bestioles aura le comportement par défaut"<<endl;
    }
    Factory fact = Factory(paramsf,proportion);
    dest.push_back(fact);
    while(!(word=="Stop"||word=="STOP")){
        if(word=="Bestioles")continue;
        else if(word=="Type"){sum+=this->readBType(source,line,dest);break;}
        else if(word.empty())cout<<"...";
        else{
            cout<<"ATTENTION: erreur de lecture: "<<word<<endl;
            break;
        }
        getline(source,line),word=this->readWord(line);

    }
}
void Interpreter::readCamoParam(string& line,string& word){
    bool correctphi=false;
    string previous;
    while(previous=word,previous!=(word=this->readWord(line))){
        if(word=="phi"){try{cpm->phi=stod((word=readWord(line),word));correctphi=true;}catch(invalid_argument){cout<<word<<endl;};}
    }
    if(correctphi){
        cpm->Add(paramsf);
        cout<<"Camouflages "<<cpm->phi<<endl;
    }
    else{
        cout<<"ATTENTION: Camouflages invalides"<<endl;
    }
}
void Interpreter::readCaraParam(string& line,string& word){
    bool correctomega=false,correcteta=false;
    string previous;
    while(previous=word,previous!=(word=this->readWord(line))){
        if(word=="omega"){try{kpm->omega=stod((word=readWord(line),word));correctomega=true;}catch(invalid_argument){cout<<word<<endl;};}
        if(word=="eta"){try{kpm->eta=stod((word=readWord(line),word));correcteta=true;}catch(invalid_argument){cout<<word<<endl;};}        
    }
    if(correctomega&&correcteta){
        kpm->Add(paramsf);
        cout<<"Carapace "<<kpm->omega<<"; "<<kpm->eta<<endl;
    }
    else{
        cout<<"ATTENTION: Carapace invalide"<<endl;
    }
}
void Interpreter::readNageoParam(string& line,string& word){
    bool correctnu=false;
    string previous;
    while(previous=word,previous!=(word=this->readWord(line))){
        if(word=="nu"){try{npm->nu=stod((word=readWord(line),word));correctnu=true;}catch(invalid_argument){cout<<word<<endl;};}
    }
    if(correctnu){
        npm->Add(paramsf);
        cout<<"Nageoire "<<npm->nu<<endl;
    }
    else{
        cout<<"ATTENTION: Nageoires invalides"<<endl;
    }
}
void Interpreter::readOreParam(string& line,string& word){
    bool correctdelta=false,correctgamma=false;
    string previous;
    while(previous=word,previous!=(word=this->readWord(line))){
        if(word=="delta"){try{opm->delta=stod((word=readWord(line),word));correctdelta=true;}catch(invalid_argument){cout<<word<<endl;};}
        if(word=="gamma"){try{opm->gamma=stod((word=readWord(line),word));correctgamma=true;}catch(invalid_argument){cout<<word<<endl;};}
    }
    if(correctdelta&&correctgamma){
        opm->Add(paramsf);
        cout<<"Oreilles "<<opm->delta<<"; "<<opm->gamma<<endl;
    }
    else{
        cout<<"ATTENTION: Oreilles invalides"<<endl;
    }
}
void Interpreter::readYeuxParam(string& line,string& word){
    bool correctdelta=false,correctgamma=false,correctalpha=false;
    string previous;
    while(previous=word,previous!=(word=this->readWord(line))){
        if(word=="delta"){try{ypm->delta=stod((word=readWord(line),word));correctdelta=true;}catch(invalid_argument){cout<<word<<endl;};}
        if(word=="gamma"){try{ypm->gamma=stod((word=readWord(line),word));correctgamma=true;}catch(invalid_argument){cout<<word<<endl;};}
        if(word=="alpha"){try{ypm->alpha=stod((word=readWord(line),word));correctalpha=true;}catch(invalid_argument){cout<<word<<endl;};}
    }
    if(correctdelta&&correctgamma&&correctalpha){
        ypm->Add(paramsf);
        cout<<"Yeux "<<ypm->delta<<"; "<<ypm->gamma<<"; "<<ypm->alpha<<endl;
    }
    else{
        cout<<"ATTENTION: Yeux invalides"<<endl;
    }
}
bool Interpreter::readComportParam(string& line,string& word){
    word=this->readWord(line);
    if(word=="Multiple")compm->Comportement=COMP_MULTIPLE;
    else if(word=="Peureuse")compm->Comportement=COMP_PEUREUSE;
    else if(word=="Kamikaze")compm->Comportement=COMP_KAMIKAZE;
    else if(word=="Prevoyante"||word=="Prévoyante")compm->Comportement=COMP_PREVOYANTE;
    else if(word=="Gregaire"||word=="Grégaire")compm->Comportement=COMP_GREGAIRE;
    else {cout<<"Comportement inconnu :"<<word<<endl;return false;}
    compm->Add(paramsf);
    cout<<"Comportement: "<<compm->Comportement<<endl;
    return true;
}
void Interpreter::fromFile(string file){
    string line;
    string word;
    ifstream input;
    bool isDefined=false;
    input.open(file);
    getline(input,line),word=this->readWord(line);
    while(!(word=="Stop"||word=="STOP")){
        if(word=="Bestioles"&&isDefined){
            while(getline(input,line),word=this->readWord(line),line.empty()){cout<<"...";}
            if(word=="Type"){
                sum+=readBType(input,line, ecosysteme->getMilieu().listeFactories);break;
            }
        }
        else if(word=="Simulation"&&!isDefined){
            while(getline(input,line),word=this->readWord(line),word=="Propriété"||word=="Propriete"||word.empty()){
                if(word.empty()){
                    cout<<"...";
                }else{
                    readProp(line);
                }
            }
            isDefined=true;
            ecosysteme=new Aquarium(Population,Width,Height, 30, this);
            continue;
        }
        else if(word.empty()){cout<<"...";}
        else{
            cout<<"ATTENTION: erreur de lecture: "<<word<<endl;
            break;
        }
        getline(input,line),word=this->readWord(line);

    }
if(sum!=1.){
    cout<<"ATTENTION: la Somme des Proportions n'est pas 1 ("<<sum<<"). Effectifs réels des Bestiole Indéfini (Sera supérieur ou inférieur à la valeur donnée)..."<<endl;
}
if(ecosysteme!=nullptr){
    cout<<"DEBUT DE LA SIMULATION"<<endl;
    ecosysteme->run();
}
}
void Interpreter::readProp(string& line){
    string word="Propriété Introuvable";
    string paramName;
    double readv;
    bool valid=false;
    float defaultvalue=0.;
    paramName=this->readWord(line);
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
    else{cout<<"ATTENTION: Propriété "<<paramName<<" inconnue..."<<endl;}
    if(!valid){cout<<"ATTENTION: Valeur illisible ou inappropriée pour la propriété "<<paramName<<": "<<word<<"... valeur remplacée par la valeur prédéfinie "<<defaultvalue<<endl;}

}