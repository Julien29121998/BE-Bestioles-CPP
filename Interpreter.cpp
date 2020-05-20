#include <iostream>
#include <fstream>
#include "Interpreter.h"

using namespace std;

Interpreter::Interpreter(){
   cpm = new CamoParams;kpm = new CaraParams;npm = new NageoParams;
   opm = new OreParams;ypm = new YeuxParams;compm = new ComportParams;
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
Factory Interpreter::readBType(ifstream& source,Aquarium& ecosysteme){
    string line;
    string word;
    float proportion=1.0;
    getline(source,line);
    word=this->readWord(line);
    cout<<"Lecture du type "<<word<<"..."<<endl;
    this->paramsf.erase(paramsf.begin(),paramsf.end());
    word=this->readWord(line);
    if(word!="p:"){
        cout<<"ATTENTION: Pas de proportion... par défaut 1, risque de produire des résultats non demandés !"<<endl;
    }
    else{
        try{
        proportion=stod(word);
        }
        catch(invalid_argument){
            cout<<"ATTENTION: \""<<word<<"\" n'est pas une proportion. Par défaut 1."<<endl;
        }
        word=this->readWord(line);
    }
    while(!word.empty()){
        cout<<"ATTENTION: Contenu non lu: "<<word<<"Sur la ligne, rien ne doit suivre la déclaration de type de bestiole"<<endl;
        word=this->readWord(line);
    }
    this->readCaracs(source,line,word);
    Factory f=Factory(paramsf,proportion);
    return f;
}
void Interpreter::readCaracs(ifstream& source,string& line,string& word){
    bool hasComp=false,valid=true;
    while(valid){
        getline(source,line),word=this->readWord(line);
        if(word=="Camouflages") this->readCamoParam(line,word);
        else if(word=="Carapace") this->readCaraParam(line,word);
        else if(word=="Nageoire") this->readNageoParam(line,word);
        else if(word=="Oreilles") this->readOreParam(line,word);
        else if(word=="Yeux") this->readYeuxParam(line,word);
        else if(word=="Comportement") hasComp=this->readComportParam(line,word);
        else {line=word+line;valid=false;};
    }
    if(!hasComp){
        cout<<"ATTENTION: Pas de Comportement Déclaré pour ce type de Bestiole: ce type de Bestioles aura le comportement par défaut"<<endl;
    }
}
void Interpreter::readCamoParam(string& line,string& word){
    bool correctphi=false;
    while(word=this->readWord(line),!word.empty()){
        if(word=="phi"){try{cpm->phi=stod((word=readWord(line),word));correctphi=true;}catch(invalid_argument){cout<<word<<endl;};}
    }
    if(correctphi){
        cpm->Add(paramsf);
    }
    else{
        cout<<"ATTENTION: Camouflages invalides"<<endl;
    }
}
void Interpreter::readCaraParam(string& line,string& word){
    bool correctomega=false,correcteta=false;
    while(word=this->readWord(line),!word.empty()){
        if(word=="omega"){try{kpm->omega=stod((word=readWord(line),word));correctomega=true;}catch(invalid_argument){cout<<word<<endl;};}
        if(word=="eta"){try{kpm->eta=stod((word=readWord(line),word));correcteta=true;}catch(invalid_argument){cout<<word<<endl;};}        
    }
    if(correctomega&&correcteta){
        kpm->Add(paramsf);
    }
    else{
        cout<<"ATTENTION: Carapace invalide"<<endl;
    }
}
void Interpreter::readNageoParam(string& line,string& word){
    bool correctnu=false;
    while(word=this->readWord(line),!word.empty()){
        if(word=="nu"){try{npm->nu=stod((word=readWord(line),word));correctnu=true;}catch(invalid_argument){cout<<word<<endl;};}
    }
    if(correctnu){
        npm->Add(paramsf);
    }
    else{
        cout<<"ATTENTION: Nageoires invalides"<<endl;
    }
}
void Interpreter::readOreParam(string& line,string& word){
    bool correctdelta=false,correctgamma=false;
    while(word=this->readWord(line),!word.empty()){
        if(word=="delta"){try{opm->delta=stod((word=readWord(line),word));correctdelta=true;}catch(invalid_argument){cout<<word<<endl;};}
        if(word=="gamma"){try{opm->gamma=stod((word=readWord(line),word));correctgamma=true;}catch(invalid_argument){cout<<word<<endl;};}
    }
    if(correctdelta&&correctgamma){
        opm->Add(paramsf);
    }
    else{
        cout<<"ATTENTION: Oreilles invalides"<<endl;
    }
}
void Interpreter::readYeuxParam(string& line,string& word){
    bool correctdelta=false,correctgamma=false,correctalpha=false;
    while(word=this->readWord(line),!word.empty()){
        if(word=="delta"){try{ypm->delta=stod((word=readWord(line),word));correctdelta=true;}catch(invalid_argument){cout<<word<<endl;};}
        if(word=="gamma"){try{ypm->gamma=stod((word=readWord(line),word));correctgamma=true;}catch(invalid_argument){cout<<word<<endl;};}
        if(word=="alpha"){try{ypm->alpha=stod((word=readWord(line),word));correctalpha=true;}catch(invalid_argument){cout<<word<<endl;};}
    }
    if(correctdelta&&correctgamma&&correctalpha){
        ypm->Add(paramsf);
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
    return true;
}
