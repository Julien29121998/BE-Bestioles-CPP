#include "Factory.h"
#define cond (it!=endit)

Factory::Factory(Param_Dict params,const double prop): proportion(prop){
    cout<<"const Factory"<<endl;
    this->setParams(params);
}
void Factory::drop(Param_Dict& pmd){
    for_each(pmd.begin(),pmd.end(), [](std::pair<string,BParams*> pair){delete pair.second;});
    pmd.erase(pmd.begin(),pmd.end());
}
void Factory::Drop(){
    drop(this->myParams);
}
void Factory::setParams(Param_Dict params){
    this->Drop();
    for(auto it=params.begin();it!=params.end();++it)
    {
        myParams.emplace(make_pair(it->first,it->second->cppm()));

    }
}

Factory::Factory(const Factory& f):Factory(f.myParams,f.proportion){
    cout<<"(par copie)"<<endl;
}

Factory& Factory::operator= (Factory f){
    this->setParams(f.myParams);
    this->proportion=f.proportion;
    return(*this);
}
Factory::~Factory(){
    this->Drop();
    cout<<"dest Factory"<<endl;

}
void Factory::fillWith(vector<DBestiole*>& toFill, int count, Milieu& monMilieu)const{
    for(int i=0; i<count;i++){
      DBestiole* bo;
      auto 
      endit=myParams.end();
      auto 
      it=myParams.find(string("Comportement"));
      if(cond){
          int comp=dynamic_cast<ComportParams*>(it->second)->Comportement;
          if(comp<0){
            bo = new Bestiole(new Multiple());
          }
          else{
            bo = new Bestiole(monMilieu.Comportements_Disponibles[comp]);
          }
      }
      else{
          bo = new Bestiole(monMilieu.Comportement_par_defaut);
      }
      it=myParams.find(string("Camouflages"));
      if(cond){
         bo = new Camouflages(bo,dynamic_cast<CamoParams*>(it->second)->phi);
      }
      it=myParams.find(string("Nageoire"));
      if(cond){
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
      bo->setExterne(bo);
      bo->initCoords(monMilieu.getWidth(),monMilieu.getHeight());
      toFill.push_back(bo);
    }

}


