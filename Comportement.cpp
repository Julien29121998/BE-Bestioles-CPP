#include "Comportement.h"
using namespace std;

void ComportParams::Add(Param_Dict& pd)
{
    PushWith(string("Comportement"),pd);
}

const int   IComportement::MULTIPLE_CHANGE_RATE=300;

IComportement::IComportement(){
    cout<<"const IC"<<endl;
}
IComportement::~IComportement(){
    cout<<"dest IC"<<endl;
}
bool IComportement::isMultiple() const{
    return false;
}

Dumb::Dumb(){
    cout<<"const Dumb"<<endl;
}
Dumb::~Dumb(){
    cout<<"dest Dumb"<<endl;
}
void Dumb::operator()(Milieu& monMilieu, DBestiole* coucheExterne){
    paire_t  info = coucheExterne->getCoords();
    coucheExterne->bouge( monMilieu,1.,info);
}
Multiple::Multiple(){
    ComportementDuMultiple=nullptr;
    cout<<"const Multiple"<<endl;
}
Multiple::~Multiple(){
    cout<<"dest Multiple"<<endl;
}
void Multiple::operator()(Milieu& monMilieu, DBestiole* coucheExterne){
    if(ComportementDuMultiple==nullptr||rand()%IComportement::MULTIPLE_CHANGE_RATE==1){
        ComportementDuMultiple=monMilieu.Comportements_Disponibles.at(rand()%monMilieu.Comportements_Disponibles.size());
    }
    (*ComportementDuMultiple)(monMilieu,coucheExterne);
}

bool Multiple::isMultiple() const{
    return true;
}

Peureuse::Peureuse(){
    cout<<"const Peureuse"<<endl;
}
Peureuse::~Peureuse(){
    cout<<"dest Peureuse"<<endl;
}
void Peureuse::operator()(Milieu& monMilieu, DBestiole* coucheExterne){
    paire_t  info = coucheExterne->getCoords();
    //CHANGER LES VALEURS DE INFO.VITE ET INFO.ORI SUIVANT LE COMPORTEMENT;
    coucheExterne->bouge( monMilieu,1.,info);
}

Prevoyante::Prevoyante(){
    cout<<"const Prevoyante"<<endl;
}
Prevoyante::~Prevoyante(){
    cout<<"dest Prevoyante"<<endl;
}
void Prevoyante::operator()(Milieu& monMilieu, DBestiole* coucheExterne){
    paire_t  info = coucheExterne->getCoords();
    //CHANGER LES VALEURS DE INFO.VITE ET INFO.ORI SUIVANT LE COMPORTEMENT;
    coucheExterne->bouge( monMilieu,1.,info);
}

Kamikaze::Kamikaze(){
    cout<<"const Kamikaze"<<endl;
}
Kamikaze::~Kamikaze(){
    cout<<"dest Kamikaze"<<endl;
}

void Kamikaze::operator()(Milieu& monMilieu, DBestiole* coucheExterne){
    paire_t  info = coucheExterne->getCoords();
    //CHANGER LES VALEURS DE INFO.VITE ET INFO.ORI SUIVANT LE COMPORTEMENT;
    coucheExterne->bouge( monMilieu,1.,info);
}

Gregaire::Gregaire(){
    cout<<"const Gregaire"<<endl;
}
Gregaire::~Gregaire(){
    cout<<"dest Gregaire"<<endl;
}

void Gregaire::operator()(Milieu& monMilieu, DBestiole* coucheExterne){
    paire_t  info = coucheExterne->getCoords();
    double vite_moy;
    double ori_moy;
    auto voisins = monMilieu.QuiVoisJe(coucheExterne);
    int size = voisins.size();
    if(size!=0){
    for(auto it=voisins.begin();it!=voisins.end();++it){
        paire_t v_info=(*it)->getCoords();
        vite_moy+=v_info.vite;
        ori_moy+=v_info.ori;
    }
    info.vite=vite_moy/size;
    info.ori=ori_moy/size;
    }
    coucheExterne->bouge( monMilieu,1.,info);
}
