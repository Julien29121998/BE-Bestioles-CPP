#include "Comportement.h"
using namespace std;

auto norm = [](double x, double y){return std::sqrt(x*x+y*y);};//Norme Euclidienne
auto carctan= [](double x, double y){return ((x!=0)?atan(y/x):M_PI/2)+((y<0)+(x*y<0)+(x<0&&!y))*M_PI;};//arctangente pour obtenir l'angle à partir des coordonnées

void ComportParams::Add(Param_Dict& pd)//Ajouter les paramètres de comportement au dictionnaire de paramètres
{
    PushWith(string("Comportement"),pd);//On les ajoute en tant que paramètres
}

BParams* ComportParams::cppm() const{//copier les paramètres de comportement
    ComportParams* p =new ComportParams();
    p->Comportement=this->Comportement;
    return p;//retourne la copie
}

int IComportement::MULTIPLE_CHANGE_RATE=300;//vitesse de changement du multiple

IComportement::IComportement(){//Constructeur
    //cout<<"const IC"<<endl;
}
IComportement::~IComportement(){//Destructeur
    //cout<<"dest IC"<<endl;
}
bool IComportement::isMultiple() const{//Un Icomportement Quelconque n'est pas multiple
    return false;
}

Dumb::Dumb(){//Constructeur
    //cout<<"const Dumb"<<endl;
}
Dumb::~Dumb(){//Destructeur
    //cout<<"dest Dumb"<<endl;
}
void Dumb::operator()(Milieu& monMilieu, DBestiole* coucheExterne){//Le Dumb va en ligne droite
    paire_t  info = coucheExterne->getCoords();
    coucheExterne->bouge( monMilieu,1.,info);
}
Multiple::Multiple(){//Constructeur Multiple
    ComportementDuMultiple=nullptr;//On prépare le comportement du multiple
    //cout<<"const Multiple"<<endl;
}
Multiple::~Multiple(){//Destructeur du multiple
    //cout<<"dest Multiple"<<endl;
}
void Multiple::operator()(Milieu& monMilieu, DBestiole* coucheExterne){//Le multiple agit:
    if(ComportementDuMultiple==nullptr||rand()%IComportement::MULTIPLE_CHANGE_RATE==1){//Si il n'en n'a pas encore ou que le hasard le décide, on change son comportement
        ComportementDuMultiple=monMilieu.Comportements_Disponibles.at(rand()%monMilieu.Comportements_Disponibles.size());//Pour cela on en pioche un dans la liste 
    }
    (*ComportementDuMultiple)(monMilieu,coucheExterne);//Puis on agit selon ce comportement
}

bool Multiple::isMultiple() const{//Le multiple est multiple et doit donc ne pas être traité en flyweight
    return true;
}

Peureuse::Peureuse(){
    //cout<<"const Peureuse"<<endl;
}
Peureuse::~Peureuse(){
    //cout<<"dest Peureuse"<<endl;
}
void Peureuse::operator()(Milieu& monMilieu, DBestiole* coucheExterne){//La peureuse fuit les groupes
    paire_t  info = coucheExterne->getCoords();//on récupère mes coordonnées
    int size=monMilieu.nbVoisins(coucheExterne);//on compte mes voisins
    if(size>=2){//si il y en a trop
        double x_sum=0;
        double y_sum=0;
        auto voisins = monMilieu.QuiVoisJe(coucheExterne);//on liste mes voisins
        for(auto it=voisins.begin();it!=voisins.end();++it){//pour tous ceux ci
            paire_t v_info=(*it)->getCoords();//on récupère leurs coordonnées
            x_sum+=v_info.vite*cos(v_info.ori);//on somme leurs x
            y_sum+=v_info.vite*sin(v_info.ori);//on somme leurs y
        }
    info.vite=info.vite*2+DBestiole::getVmax()/2;//On accélère
    info.ori=-carctan(x_sum,y_sum);//l'orientation souhaitée est l'opposée de la moyenne des voisines. On veut les fuir. On utilise les sommes calculées.
    }
    else{//sinon vitesse et orientation sont aléatoires
        info.ori=info.ori+fmod(rand(),M_PI/4)-M_PI/8;
        info.vite=static_cast<float>(rand())/RAND_MAX*DBestiole::getVmax();
    }
    coucheExterne->bouge( monMilieu,1.,info);
}

Prevoyante::Prevoyante(){//Constructeur
    //cout<<"const Prevoyante"<<endl;
}
Prevoyante::~Prevoyante(){//Destructeur
    //cout<<"dest Prevoyante"<<endl;
}
void Prevoyante::operator()(Milieu& monMilieu, DBestiole* coucheExterne){//La prevoyante évite les collisions
    paire_t  info = coucheExterne->getCoords();//mes coordonnées
    paire_t v_info;//coordonnées des autres
    double distance_min=static_cast<double>(INFINITY);//initialisation du minimum
    auto voisins = monMilieu.QuiVoisJe(coucheExterne);//je cherche mes voisins
    DBestiole* proie=nullptr;//ma future "proie" à éviter
    for(auto it=voisins.begin();it!=voisins.end();++it){//pour tous mes voisins
        v_info=(*it)->getCoords();//je récupère leurs coordonnées
        double norme = norm(
        v_info.x+v_info.vite*cos(v_info.ori)
        -info.x-info.vite*cos(info.ori),
        v_info.y+v_info.vite*sin(v_info.ori)
        -info.y-info.vite*sin(info.ori));//j'évalue la distance à laquelle nous serons à la prohaine époque, après déplacement
        if(norme<distance_min){//Si c'est plus petit, c'est un pas de plus vers le minimum
            distance_min=norme;
            proie=(*it);
        }
    }//Ici, on a pu déterminer la "proie" de l'évitement

    info.vite=static_cast<float>(rand())/RAND_MAX*DBestiole::getVmax();//Vitesse aléatoire

    if(proie!=nullptr){//si j'ai trouvé une bestiole à éviter
        v_info = proie->getCoords();//ses coordnnées
        double difx = v_info.x-info.x;//différence de position
        double dify = v_info.y-info.y;//différence de position
        int signe = ((dify)*cos(info.ori)-(difx)*sin(info.ori))>0?1:-1;//signe du produit scalaire avec le vecteur orthogonal gauche. Détermine dans quel sens il ne faut pas tourner
        info.ori=carctan(signe*(dify+v_info.vite*sin(v_info.ori)),-signe*(difx+v_info.vite*cos(v_info.ori)));//On tourne dans le sens nécessaire pour éviter la bestiole
    }
    else{//si je suis seul, mon orientation est aléatoire   
        info.ori=info.ori+fmod(rand(),M_PI/4)-M_PI/8;
    }

    coucheExterne->bouge( monMilieu,1.,info);
}

Kamikaze::Kamikaze(){//Constructeur
    //cout<<"const Kamikaze"<<endl;
}
Kamikaze::~Kamikaze(){//Destructeur
    //cout<<"dest Kamikaze"<<endl;
}

void Kamikaze::operator()(Milieu& monMilieu, DBestiole* coucheExterne){//Le Kamikaze va vers sa proie
    double Kamikaze_val=0.5;//Coefficient de vitesse du kamikaze
    paire_t  info = coucheExterne->getCoords();//mes coordonnées
    paire_t v_info;//coordonnées des voisins
    double distance_min=static_cast<double>(INFINITY);//futur minimum
    auto voisins = monMilieu.QuiVoisJe(coucheExterne);//mes voisins
    DBestiole* proie=nullptr;//future proie vers laquelle se diriger
    for(auto it=voisins.begin();it!=voisins.end();++it){//pour tous mes voisins
        v_info=(*it)->getCoords();//leurs coordonnées
        double norme = norm(v_info.x-info.x,v_info.y-info.y);//distance entre nous
        if(norme<distance_min){//si c'est un nouveau minimum, on le garde
            distance_min=norme;
            proie=(*it);
        }
    }
    if(proie!=nullptr){//si on a trouvé une proie
        v_info = proie->getCoords();//on récupère ses coordonnées
        info.vite=(1+Kamikaze_val)*v_info.vite;//On va plus vite que sa proie
        info.ori=carctan(v_info.x+v_info.vite*cos(v_info.ori)-info.x,v_info.y+v_info.vite*sin(v_info.ori)-info.y);//On se dirige vers elle
    }
    else{//sinon
        info.vite-=Kamikaze_val;//On ralentit
        info.vite=(info.vite<(DBestiole::getVmax()/5)?DBestiole::getVmax()/5:info.vite);//jusqu'à une vitesse faible
    }
    coucheExterne->bouge( monMilieu,1.,info);
}

Gregaire::Gregaire(){//Constructeur
    //cout<<"const Gregaire"<<endl;
}
Gregaire::~Gregaire(){//Destructeur
    //cout<<"dest Gregaire"<<endl;
}

void Gregaire::operator()(Milieu& monMilieu, DBestiole* coucheExterne){//Imiter ses voisins
    paire_t  info = coucheExterne->getCoords();//mes coordonnées
    double x_sum=0;
    double y_sum=0;
    auto voisins = monMilieu.QuiVoisJe(coucheExterne);//mes voisins
    int size = voisins.size();//leur effectif
    if(size!=0){//Si il y en a
    for(auto it=voisins.begin();it!=voisins.end();++it){//pour chacun d'eux
        paire_t v_info=(*it)->getCoords();//leurs coordonnées
        x_sum+=v_info.vite*cos(v_info.ori);//on fait la moyenne
        y_sum+=v_info.vite*sin(v_info.ori);//on fait la moyenne
    }
    info.vite=norm(x_sum,y_sum)/size;//ma vitesse est la moyenne
    info.ori=carctan(x_sum,y_sum);//ma vitesse est la moyenne
    }
    coucheExterne->bouge( monMilieu,1.,info);
}
