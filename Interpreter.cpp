#include <iostream>
#include <fstream>
#include "Interpreter.h"

using namespace std;

Interpreter::Interpreter(){
   cpm = new CamoParams;kpm = new CaraParams;npm = new NageoParams;
   opm = new OreParams;ypm = new YeuxParams;compm = new ComportParams;
   sum=0.0;
}
Interpreter::~Interpreter(){
   delete cpm;delete kpm;delete npm;delete opm;delete ypm;delete compm;
}
string Interpreter::readWord(string& line){
    string word;
    int found = line.find(" ");
    word=line.substr(0,found);
    line=line.substr(found+1,line.size());
    return word;
}
double Interpreter::readBType(ifstream& source, string first_line, vector<Factory>& dest){
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
void Interpreter::readCaracs(ifstream& source, string first_line, vector<Factory>& dest, double proportion){
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
        else {break;};
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
    else if(word=="Peurese")compm->Comportement=COMP_PEUREUSE;
    else if(word=="Kamikaze")compm->Comportement=COMP_KAMIKAZE;
    else if(word=="Prevoyante"||word=="Prévoyante")compm->Comportement=COMP_PREVOYANTE;
    else if(word=="Gregaire"||word=="Grégaire")compm->Comportement=COMP_GREGAIRE;
    else {return false;}
    compm->Add(paramsf);
    cout<<"Comportement: "<<compm->Comportement<<endl;
    return true;
}
void Interpreter::fromFile(string file,Aquarium& ecosysteme){
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
                sum+=readBType(input,line, ecosysteme.getMilieu().listeFactories);break;
            }
        }
        else if(word=="Simulation"){
            cout<<"UNIMPLEMENTED"<<endl;
            isDefined=true;
        }
        else if(word.empty()){cout<<"...";}
        else{
            cout<<"ATTENTION: erreurs de lecture: "<<word<<endl;
            break;
        }
        getline(input,line),word=this->readWord(line);

    }
if(sum!=1.){
    cout<<"ATTENTION: la Somme des Proportions n'est pas 1. Effectifs réels des Bestiole Indéfini..."<<endl;
}
}