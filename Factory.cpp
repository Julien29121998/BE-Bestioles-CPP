#include "Factory.h"
#define cond (it!=endit)

BParams::~BParams(){}
void BParams::PushWith(string key, Param_Dict& pd){
    pd.emplace(make_pair(key,this));
    cout<<pd.size()<<endl;
}
void CamoParams::Add(Param_Dict& pd){
    PushWith(string("Camouflages"),pd);
}
void NageoParams::Add(Param_Dict& pd){
    PushWith(string("Nageoire"),pd);
}
void CaraParams::Add(Param_Dict& pd){
    PushWith(string("Carapace"),pd);
}
void OreParams::Add(Param_Dict& pd){
    PushWith(string("Oreilles"),pd);
}
void YeuxParams::Add(Param_Dict& pd){
    PushWith(string("Yeux"),pd);
}

Factory::Factory(Param_Dict params,const double prop): proportion(prop){
    cout<<"const Factory"<<endl;
    this->setParams(params);
    cout<<myParams.size()<<endl;
}
void Factory::setParams(Param_Dict params){
    myParams=Param_Dict(params.begin(),params.end());
}
Param_Dict* Factory::getParams(){
    return &myParams;
}

Factory::Factory(const Factory& f):Factory(f.myParams,f.proportion){
    cout<<"(par copie)"<<endl;
}

Factory& Factory::operator= (Factory f){
    this->myParams=f.myParams;
    this->proportion=f.proportion;
    return(*this);
}
Factory::~Factory(){
    cout<<"dest Factory"<<endl;

}
void Factory::fillWith(vector<DBestiole*>& toFill, int count, int width, int height)const{
    cout<<myParams.size()<<endl;
    for(int i=0; i<count;i++){
      DBestiole* bo = new Bestiole();
      DBestiole* lowest_layer = bo;
      auto 
      endit=myParams.end();
      auto 
      it=myParams.find(string("Camouflages"));
      if(cond){
         bo = new Camouflages(bo,dynamic_cast<CamoParams*>(it->second)->phi);
      }
      it=myParams.find(string("Nageoire"));
      if(cond){
          cout<<"vu !"<<endl;
         bo = new Nageoire(bo,dynamic_cast<NageoParams*>(it->second)->nu);
      }
      it=myParams.find(string("Carapace"));
      if(cond){
         bo = new Carapace(bo,dynamic_cast<CaraParams*>(it->second)->omega,
         dynamic_cast<CaraParams*>(it->second)->eta);
      }
      it=myParams.find(string("Oreilles"));
      if(cond){
         bo = new Oreilles(bo,dynamic_cast<OreParams*>(it->second)->delta,
         dynamic_cast<OreParams*>(it->second)->gamma);
      }
      it=myParams.find(string("Yeux"));
      if(cond){
         bo = new Yeux(bo,dynamic_cast<YeuxParams*>(it->second)->delta,
         dynamic_cast<YeuxParams*>(it->second)->gamma,
         dynamic_cast<YeuxParams*>(it->second)->alpha);
      }
      lowest_layer->setExterne(bo);
      bo->initCoords(width,height);
      toFill.push_back(bo);
    }

}


