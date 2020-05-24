#ifndef _FACTORY_H_
#define _FACTORY_H_

#include "DBestiole.h"
#include "Bestiole.h"
#include "Camouflages.h"
#include "Nageoire.h"
#include "Carapace.h"
#include "Oreilles.h"
#include "Yeux.h"

#include <iostream>
#include <vector>
#include <map>

class Milieu;

using namespace std;
/**Factory pour créer des bestioles d'un même type plusieurs fois*/
class Factory final{
private:
    Param_Dict myParams;//le dictionnaire de paramètres de construction
    string type;//le nom du type
public:
    /**La proportion de ce type dans la simulation*/
    double proportion;
    /**Constructeur de Factory*/
    Factory(Param_Dict params,const double proportion,string type);
    /**Constructeur de Factory par copie*/
    Factory(const Factory& f);
    /**Assignement*/
    Factory& operator= (Factory f);
    /**Définir le dictionnaire de paramètres*/
    void setParams(Param_Dict params);
    /**Remplir une liste avec des bestioles créées par cette factory*/
    void fillWith(vector<DBestiole*>& toFill, int count,Milieu& monMilieu)const;
    /**Destructeur de Factory*/
    ~Factory();
    /**Jeter un dictionnaire de paramètres*/
    static void drop(Param_Dict& pmd);
    /**Jeter le dictionnaire de paramètres de cette factory*/
    void Drop();
    /**Récuperer le nom de type de ce qui est généré par cette factory*/
    string getTypeName() const;
};
#endif