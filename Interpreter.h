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
/**Interpréteur: exploiter un fichier pour lancer une simulation*/
struct Interpreter final{
public:
    static const string OutputFile;//constantes pour le fichier de retour
    static const string Others;//constantes pour le fichier de retour
private:
    //Paramètres pour initialiser les factories
    Param_Dict paramsf;
    CamoParams* cpm;
    CaraParams* kpm;
    NageoParams* npm;
    OreParams* opm;
    YeuxParams* ypm;
    ComportParams* compm;
    //Aquarium à créer
    Aquarium* ecosysteme;
    //Somme des proportions
    double sum;
    //Population visée
    int Population=64;
    //Taille de la fenêtre
    int Height=600;
    int Width=800;
public:
    /**Constructeur de l'interpréteur*/
    Interpreter();
    /**Destructeur de l'interpréteur*/
    ~Interpreter();
    /**Lire le fichier pour créer une simulation*/
    void fromFile(string File);
    /**Lire un type de créature*/
    double readBType(istream& source, string first_line, vector<Factory>& dest);
    /**découper un mot*/
    string readWord(string& source);
private:
    /**Lire les carctéristiques de Bestiole*/
    void readCaracs(istream& source, string first_line, vector<Factory>& dest, double proportion, string type);
    /**Lire des paramètres de camouflage*/
    void readCamoParam(string& line,string& word);
    /**Lire des paramètres de carapace*/
    void readCaraParam(string& line,string& word);
    /**Lire des paramètres de nageoire*/
    void readNageoParam(string& line,string& word);
    /**Lire des paramètres d'oreilles*/
    void readOreParam(string& line,string& word);
    /**Lire des paramètres d'yeux*/
    void readYeuxParam(string& line,string& word);
    /**Lire les paramètres de comportement*/
    bool readComportParam(string& line,string& word);
    /**Lire une propriété de simulation*/
    void readProp(string& line);
};


#endif