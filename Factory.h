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

class Factory final{
private:
    Param_Dict myParams;
public:
    double proportion;
    Factory(Param_Dict params,const double proportion);
    Factory(const Factory& f);
    Factory& operator= (Factory f);
    void setParams(Param_Dict params);
    Param_Dict* getParams();
    ~Factory();
    void fillWith(vector<DBestiole*>& toFill, int count,Milieu& monMilieu)const;
};
#endif