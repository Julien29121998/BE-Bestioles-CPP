#include "Factory.h"
#define cond (it!=endit)

Factory::Factory(Param_Dict params,const double prop,string type): type(type),proportion(prop){//Constructeur
   // cout<<"const Factory"<<endl;
    this->setParams(params);
}
void Factory::drop(Param_Dict& pmd){//Jeter le dictionnaire de paramètres de cette factory
    for_each(pmd.begin(),pmd.end(), [](std::pair<string,BParams*> pair){delete pair.second;});//on supprime tous les paramètres
    pmd.erase(pmd.begin(),pmd.end());//on efface le dictionnaire
}
void Factory::Drop(){// version non statique de la fonction précédente
    drop(this->myParams);
}
void Factory::setParams(Param_Dict params){//Attribuer un dictionnaire de paramètres à cette factory
    this->Drop();//on vide l'ancien
    for(auto it=params.begin();it!=params.end();++it)
    {
        myParams.emplace(make_pair(it->first,it->second->cppm()));//On ajoute le nouveau, paire par paire, en se basant sur l'argument 

    }
}

Factory::Factory(const Factory& f):Factory(f.myParams,f.proportion,f.type){//constructeur par copie
    //cout<<"(par copie)"<<endl;
}

Factory& Factory::operator= (Factory f){//opérateur d'assignement
    this->setParams(f.myParams);
    this->proportion=f.proportion;
    return(*this);
}
Factory::~Factory(){//destructeur
    this->Drop();//on jette le dictionnaire
    //cout<<"dest Factory"<<endl;

}
void Factory::fillWith(vector<DBestiole*>& toFill, int count, Milieu& monMilieu)const{//on remplit une liste avec les bestioles de cette factory
    for(int i=0; i<count;i++){//Autant de fois que requis
      DBestiole* bo;//la bestiole qui va être créée
      auto 
      endit=myParams.end();
      auto 
      it=myParams.find(string("Comportement"));//on cherche le comportement
      if(cond){
          int comp=dynamic_cast<ComportParams*>(it->second)->Comportement;//on le lit en tant que paramètre de comportement
          if(comp<0){
            bo = new Bestiole(new Multiple());//Si c'est un multiple on le crée en tant que comportement unique d'une bestiole
          }
          else{
            bo = new Bestiole(monMilieu.Comportements_Disponibles[comp]);//sinon on attribue le flyweight correspondant à la nouvelle bestiole
          }
      }
      else{
          bo = new Bestiole(monMilieu.Comportement_par_defaut);//sinon comportement par défaut
      }
      it=myParams.find(string("Camouflages"));//on cherche le camouflage
      if(cond){
         bo = new Camouflages(bo,dynamic_cast<CamoParams*>(it->second)->phi);//on crée un décorateur camouflage autour de la bestiole
      }
      it=myParams.find(string("Nageoire"));//on cherche une nageoire
      if(cond){
         bo = new Nageoire(bo,dynamic_cast<NageoParams*>(it->second)->nu);//on crée un décorateur nageoire autour de la bestiole
      }
      it=myParams.find(string("Carapace"));//on cherche une carapace
      if(cond){
         bo = new Carapace(bo,dynamic_cast<CaraParams*>(it->second)->omega,
         dynamic_cast<CaraParams*>(it->second)->eta);//on crée un décorateur carapace autour de la bestiole
      }
      it=myParams.find(string("Oreilles"));//on cherche des oreilles
      if(cond){
         bo = new Oreilles(bo,dynamic_cast<OreParams*>(it->second)->delta,
         dynamic_cast<OreParams*>(it->second)->gamma);//on crée un décorateur oreilles autour de la bestiole
      }
      it=myParams.find(string("Yeux"));//on cherche des yeux
      if(cond){
         bo = new Yeux(bo,dynamic_cast<YeuxParams*>(it->second)->delta,
         dynamic_cast<YeuxParams*>(it->second)->gamma,
         dynamic_cast<YeuxParams*>(it->second)->alpha);//on crée un décorateur yeux autour de la bestiole
      }
      bo->setExterne(bo);//on enseigne à la bestiole la plus extérieure de ses couches de décorateurs
      bo->setType(type);//on enseigne à la bestiole son type
      bo->initCoords(monMilieu.getWidth(),monMilieu.getHeight());//on initialise aléatoirement ses coordonnées
      toFill.push_back(bo);//on envoie la nouvelle bestiole dans la liste
    }

}
string Factory::getTypeName() const{//récupérer le nom de type de ce que crée cette factory
    return type;//renvoie le type
}


