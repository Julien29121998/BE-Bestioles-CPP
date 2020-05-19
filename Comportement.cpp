#include "Comportement.h"
using namespace std;

auto norm = [](double x, double y){return std::sqrt(x*x+y*y);};
auto carctan= [](double x, double y){return ((x!=0)?atan(y/x):M_PI/2)+((y<0)+(x*y<0)+(x<0&&!y))*M_PI;};

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
    int size=monMilieu.nbVoisins(coucheExterne);
    if(size>=2){
        double x_sum=0;
        double y_sum=0;
        auto voisins = monMilieu.QuiVoisJe(coucheExterne);
        for(auto it=voisins.begin();it!=voisins.end();++it){
            paire_t v_info=(*it)->getCoords();
            x_sum+=v_info.vite*cos(v_info.ori);
            y_sum+=v_info.vite*sin(v_info.ori);
        }
    info.vite=info.vite*2+DBestiole::getVmax()/2;
    info.ori=-carctan(x_sum,y_sum);
    }
    else{
        info.ori=info.ori+fmod(rand(),M_PI/4)-M_PI/8;
        info.vite=static_cast<float>(rand())/RAND_MAX*DBestiole::getVmax();
    }
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
    paire_t v_info;
    double distance_min=static_cast<double>(INFINITY);
    auto voisins = monMilieu.QuiVoisJe(coucheExterne);
    DBestiole* proie=nullptr;
    for(auto it=voisins.begin();it!=voisins.end();++it){
        v_info=(*it)->getCoords();
        double norme = norm(
        v_info.x+v_info.vite*cos(v_info.ori)
        -info.x-info.vite*cos(info.ori),
        v_info.y+v_info.vite*sin(v_info.ori)
        -info.y-info.vite*sin(info.ori));
        if(norme<distance_min){
            distance_min=norme;
            proie=(*it);
        }
    }

    info.vite=static_cast<float>(rand())/RAND_MAX*DBestiole::getVmax();

    if(proie!=nullptr){
        v_info = proie->getCoords();
        double difx = v_info.x-info.x;
        double dify = v_info.y-info.y;
        int signe = ((dify)*cos(info.ori)-(difx)*sin(info.ori))>0?1:-1;
        info.ori=carctan(signe*(dify+v_info.vite*sin(v_info.ori)),-signe*(difx+v_info.vite*cos(v_info.ori)));
    }
    else{        
        info.ori=info.ori+fmod(rand(),M_PI/4)-M_PI/8;
    }

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
    paire_t v_info;
    double distance_min=static_cast<double>(INFINITY);
    auto voisins = monMilieu.QuiVoisJe(coucheExterne);
    DBestiole* proie=nullptr;
    for(auto it=voisins.begin();it!=voisins.end();++it){
        v_info=(*it)->getCoords();
        double norme = norm(v_info.x-info.x,v_info.y-info.y);
        if(norme<distance_min){
            distance_min=norme;
            proie=(*it);
        }
    }
    if(proie!=nullptr){
        v_info = proie->getCoords();
        info.vite=v_info.vite+0.5*norm(v_info.x-info.x,v_info.y-info.y);
        info.ori=carctan(v_info.x-info.x,v_info.y-info.y);
    }
    else{
        info.vite-=0.5;
        info.vite=(info.vite<(DBestiole::getVmax()/5)?DBestiole::getVmax()/5:info.vite);
    }
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
    double x_sum=0;
    double y_sum=0;
    auto voisins = monMilieu.QuiVoisJe(coucheExterne);
    int size = voisins.size();
    if(size!=0){
    for(auto it=voisins.begin();it!=voisins.end();++it){
        paire_t v_info=(*it)->getCoords();
        x_sum+=v_info.vite*cos(v_info.ori);
        y_sum+=v_info.vite*sin(v_info.ori);
    }
    info.vite=norm(x_sum,y_sum)/size;
    info.ori=carctan(x_sum,y_sum);
    }
    coucheExterne->bouge( monMilieu,1.,info);
}
