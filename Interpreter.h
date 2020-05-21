#ifndef __SIMU_BUILDER__f_H_
#define __SIMU_BUILDER__f_H_
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

struct Interpreter final{
private:
    Param_Dict paramsf;
    CamoParams* cpm;
    CaraParams* kpm;
    NageoParams* npm;
    OreParams* opm;
    YeuxParams* ypm;
    ComportParams* compm;
    double sum;
public:
    Interpreter();
    ~Interpreter();
    void fromFile(string File,Aquarium& ecosysteme);
    double readBType(ifstream& source, string first_line, vector<Factory>& dest);
    string readWord(string& source);
private:
    void readCaracs(ifstream& source, string first_line, vector<Factory>& dest, double proportion);
    void readCamoParam(string& line,string& word);
    void readCaraParam(string& line,string& word);
    void readNageoParam(string& line,string& word);
    void readOreParam(string& line,string& word);
    void readYeuxParam(string& line,string& word);
    bool readComportParam(string& line,string& word);
    void nextBlock();

};


#endif