#include "Comportement.h"
using namespace std;

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
    if(rand()%18==1){
        cout<<coucheExterne->showID()<<" is Dumb"<<endl;
    }
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
        cout<<"change multiple "<<typeid(ComportementDuMultiple).name()<<endl;
    }
    if(rand()%18==1){
        cout<<(coucheExterne->showID())<<" is Multiple with : ";
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
    if(rand()%18==1){
        cout<<coucheExterne->showID()<<" is Peureuse"<<endl;
    }
}

Prevoyante::Prevoyante(){
    cout<<"const Prevoyante"<<endl;
}
Prevoyante::~Prevoyante(){
    cout<<"dest Prevoyante"<<endl;
}
void Prevoyante::operator()(Milieu& monMilieu, DBestiole* coucheExterne){
    if(rand()%18==1){
        cout<<coucheExterne->showID()<<" is Prevoyante"<<endl;
    }
}

Kamikaze::Kamikaze(){
    cout<<"const Kamikaze"<<endl;
}
Kamikaze::~Kamikaze(){
    cout<<"dest Kamikaze"<<endl;
}

void Kamikaze::operator()(Milieu& monMilieu, DBestiole* coucheExterne){
    if(rand()%18==1){
        cout<<coucheExterne->showID()<<" is Kamikaze"<<endl;
    }
}

Gregaire::Gregaire(){
    cout<<"const Gregaire"<<endl;
}
Gregaire::~Gregaire(){
    cout<<"dest Gregaire"<<endl;
}

void Gregaire::operator()(Milieu& monMilieu, DBestiole* coucheExterne){
    if(rand()%18==1){
        cout<<coucheExterne->showID()<<" is Gregaire"<<endl;
    }
}
