#include "Comportement.h"
using namespace std;

void ComportParams::Add(Param_Dict& pd)
{
    PushWith(string("Comportement"),pd);
}

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
    if(ComportementDuMultiple==nullptr||rand()%300==1){
        ComportementDuMultiple=monMilieu.Comportements_Disponibles.at(rand()%monMilieu.Comportements_Disponibles.size());
    }
    if(rand()%18==1){
        (*ComportementDuMultiple)(monMilieu,coucheExterne);
    }
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
    coucheExterne->bouge( monMilieu,1.,info);
}
