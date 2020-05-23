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
public:
    static const string OutputFile;
    static const string Others;
private:
    Param_Dict paramsf;
    CamoParams* cpm;
    CaraParams* kpm;
    NageoParams* npm;
    OreParams* opm;
    YeuxParams* ypm;
    ComportParams* compm;
    Aquarium* ecosysteme;
    double sum;
    int Population=64;
    int Height=600;
    int Width=800;
public:
    Interpreter();
    ~Interpreter();
    void fromFile(string File);
    double readBType(istream& source, string first_line, vector<Factory>& dest);
    string readWord(string& source);
private:
    void readCaracs(istream& source, string first_line, vector<Factory>& dest, double proportion, string type);
    void readCamoParam(string& line,string& word);
    void readCaraParam(string& line,string& word);
    void readNageoParam(string& line,string& word);
    void readOreParam(string& line,string& word);
    void readYeuxParam(string& line,string& word);
    bool readComportParam(string& line,string& word);
    void readProp(string& line);
};


#endif