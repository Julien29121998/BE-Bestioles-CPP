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
struct BParams;

using namespace std;
using Param_Dict = std::map<std::string,BParams*>;

struct BParams{
virtual ~BParams();
void PushWith(string key,Param_Dict& pd);
virtual void Add(Param_Dict& pd)=0;
};
struct CamoParams:BParams{double phi;virtual void Add(Param_Dict& pd) override;};
struct NageoParams:BParams{double nu;virtual void Add(Param_Dict& pd) override;};
struct CaraParams:BParams{double omega;double eta;virtual void Add(Param_Dict& pd) override;};
struct OreParams:BParams{double delta;double gamma;virtual void Add(Param_Dict& pd) override;};
struct YeuxParams:BParams{double delta;double gamma;double alpha;virtual void Add(Param_Dict& pd) override;};

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
    void fillWith(vector<DBestiole*>& toFill, int count, int width, int height)const;
};
#endif